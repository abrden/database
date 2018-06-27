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

Response* Server::insert_entry(const std::string& name, const size_t name_size,
                               const std::string& address, const size_t address_size,
                               const std::string& phone, const size_t phone_size) {
    std::cout << "ns " << name_size << std::endl;
    std::cout << "as " << address_size << std::endl;
    std::cout << "ps " << phone_size << std::endl;

    Response* r;
    try {
        db.insert_entry(name, name_size, address, address_size, phone, phone_size);
        r = new Response(true, "Success: Entry inserted", QUERY_TYPE::INSERT);
    } catch (const std::runtime_error& e) {
        r = new Response(false, e.what(), QUERY_TYPE::INSERT);
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
            response = insert_entry(query.get_name(), query.get_name_size(),
                                    query.get_address(), query.get_address_size(),
                                    query.get_phone(), query.get_phone_size());
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