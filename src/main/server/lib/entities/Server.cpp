#include "Server.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <system_error>
#include <cstring>

#include "SignalHandler.h"

Server::Server(const std::string& queue_file, const char queue_letter, std::string db_file)
        : file(db_file), queue(queue_file, queue_letter) {
    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void Server::entries_to_file() {
    int fd = open(file.c_str(), O_WRONLY | O_CREAT, 0666);

    for (auto const& entry : entries) {
        std::string entry_str = entry->to_string();
        std::cout << "[SERVER] Writing to file : " << entry_str << std::endl;
        ssize_t bytes_written = write(fd, entry_str.c_str(), entry_str.size());
        if ((unsigned long) bytes_written != entry_str.size()) {
            close(fd);

            std::string message = std::string("Error in write: could not write db file: ") + std::string(strerror(errno));
            throw std::system_error(errno, std::system_category(), message);
        }
    }

    close(fd);
}

Response* Server::select_entries(const std::string& name,
                                 const std::string& address,
                                 const std::string& phone) const {
    // TODO select entries
    const std::vector<Entry*> l;
    Response* r = new Response(true, "Todo liso", QUERY_TYPE::SELECT, l);

    return r;
}

Response* Server::insert_entry(const std::string& name,
                          const std::string& address,
                          const std::string& phone) {
    // TODO check if entry exists
    Entry* entry = new Entry(name, address, phone);
    entries.push_back(entry);

    Response* r = new Response(true, "ATR perro", QUERY_TYPE::INSERT);
    
    return r;
}

void Server::run() {
    while (sigint_handler.get_graceful_quit() == 0) {
        ClientMessage cmsg = queue.pop();
        Query query = cmsg.get_query();
        Response* response;
        if (query.get_operation() == SELECT) {
            response = select_entries(query.get_name(), query.get_address(), query.get_phone());
        } if (query.get_operation() == INSERT) {
            response = insert_entry(query.get_name(), query.get_address(), query.get_phone());
        }
        ServerMessage smsg(cmsg.get_mtype(), *response);
        queue.push(smsg);
    }
}

Server::~Server() {
    entries_to_file();
    while (!entries.empty()) {
        delete entries.back();
        entries.pop_back();
    }
    SignalHandler::destroy();
}