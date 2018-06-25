#include "Server.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <system_error>
#include <cstring>

#include "SignalHandler.h"

Server::Server(const std::string& queue_file, const char queue_letter, std::string db_file)
        : db(db_file), queue(queue_file, queue_letter) {
    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

Response* Server::select_entries(const std::string& name,
                                 const std::string& address,
                                 const std::string& phone) const {
    std::vector<Entry*> entries = db.select_entries(name, address, phone);
    return new Response(true, "Success, sending matching entries", QUERY_TYPE::SELECT, entries);
}

Response* Server::insert_entry(const std::string& name,
                          const std::string& address,
                          const std::string& phone) {
    Response* r;
    try {
        db.insert_entry(name, address, phone);
        r = new Response(true, "Success: Entry inserted", QUERY_TYPE::INSERT);
    } catch (const std::runtime_error&) {
        r = new Response(false, "Error: Entry already exists in the database", QUERY_TYPE::INSERT);
    }

    return r;
}

void Server::run() {
    while (sigint_handler.get_graceful_quit() == 0) {
        ClientMessage* cmsg = queue.pop();
        if (!cmsg) continue;
        Query query = cmsg->get_query();
        Response* response;
        if (query.get_operation() == SELECT) {
            std::cout << "Selecting query with name: " << query.get_name() << ", address: " << query.get_address() << ", phone: " << query.get_phone() << std::endl;
            response = select_entries(query.get_name(), query.get_address(), query.get_phone());
            std::string status = response->get_ok() ? "Success" : "Error";
            std::cout << status << std::endl;
        } if (query.get_operation() == INSERT) {
            std::cout << "Inserting query with name: " << query.get_name() << ", address: " << query.get_address() << ", phone: " << query.get_phone() << std::endl;
            response = insert_entry(query.get_name(), query.get_address(), query.get_phone());
            std::string status = response->get_ok() ? "Success" : "Error";
            std::cout << status << std::endl;
        }
        ServerMessage smsg(cmsg->get_sender_id(), response);
        queue.push(smsg);
        delete cmsg;
    }
}

Server::~Server() {
    SignalHandler::destroy();
}