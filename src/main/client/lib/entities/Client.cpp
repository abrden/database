#include "Client.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Entry.h"
#include "Query.h"
#include "SignalHandler.h"

Client::Client(const std::string &queue_file, const char queue_letter) : queue(queue_file, queue_letter) {
    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

Response* Client::get_entry(const std::string& name, const std::string& address, const std::string& phone) {
    Query query(QUERY_TYPE::SELECT, name, address, phone);
    ClientMessage cmsg(getpid(), query);
    queue.push(cmsg);

    ServerMessage* smsg = queue.pop(getpid());
    Response* response = smsg->get_response();

    delete smsg;

    return response;
}

Response* Client::insert_entry(const std::string &name, const std::string &address, const std::string &phone) {
    Query query(QUERY_TYPE::INSERT, name, address, phone);
    ClientMessage cmsg(getpid(), query);
    queue.push(cmsg);

    ServerMessage* smsg = queue.pop(getpid());
    Response* response = smsg->get_response();

    delete smsg;

    return response;
}

void Client::run() {
    std::string line;
    std::cout << "Make a query (insert <name,address,phone>, select <name,address,phone>) or just exit." << std::endl;
    std::cout << "> ";
    std::getline(std::cin, line);
    while (line != "exit" && sigint_handler.get_graceful_quit() == 0) {
        std::stringstream ss(line);
        std::string op;
        std::getline(ss, op, ' ');
        std::string arg;
        std::getline(ss, arg, '\n');

        if (op == "insert") {
            // Es necesario un lock??
            Entry entry(arg);
            std::cout << "Inserting entry: " << entry << std::endl;

            Response* response = insert_entry(entry.get_name(), entry.get_address(), entry.get_phone());
            std::cout << response->get_message() << std::endl;
            delete response;

        } else if (op == "select") {
            // Es necesario un lock??
            Entry entry(arg);
            std::cout << "Selecting entries: " << entry << std::endl;

            Response* response = get_entry(entry.get_name(), entry.get_address(), entry.get_phone());
            if (response->get_ok()) {
                std::vector<Entry*> selection = response->get_selection();
                std::cout << selection.size() << " results." << std::endl;
                for (std::vector<Entry*>::iterator it = selection.begin(); it != selection.end(); ++it) {
                    std::cout << *(*it) << std::endl;
                }
            } else {
                std::cout << "Error: " << response->get_message() << std::endl;
            }
            delete response;

        } else if (!op.empty()) {
            std::cout << "Invalid query, try again" << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, line);
    }
}

Client::~Client() {
    SignalHandler::destroy();
}