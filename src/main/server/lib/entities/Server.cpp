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
    Entry entry(name, address, phone);
    std::vector<Entry*> entries = db.select_entries(&entry);
    return new Response(true, "Success, sending matching entries", QUERY_TYPE::SELECT, entries);
}

Response* Server::insert_entry(const std::string& name,
                          const std::string& address,
                          const std::string& phone) {
    Entry entry(name, address, phone);
    Response* r;
    if (db.entry_exists(&entry)) {
        r = new Response(false, "Error on INSERT: entry already exists in the database", QUERY_TYPE::INSERT);
    } else {
        db.insert_entry(&entry);
        r = new Response(true, "Success, entry inserted", QUERY_TYPE::INSERT);
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
            response = select_entries(query.get_name(), query.get_address(), query.get_phone());
        } if (query.get_operation() == INSERT) {
            response = insert_entry(query.get_name(), query.get_address(), query.get_phone());
        }
        ServerMessage smsg(cmsg->get_mtype(), response);
        queue.push(smsg);
        delete cmsg;
    }
}

Server::~Server() {
    SignalHandler::destroy();
}