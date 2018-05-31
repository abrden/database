#include "Client.h"

#include <iostream>
#include <sstream>

Client::Client(key_t queue_key) : queue(queue_key) {}

bool Client::get_entry(std::string& name) {
    // TODO print matching entries
    return false;
}

bool Client::add_entry(std::string& entry_str) {
    Entry entry(entry_str);

    // TODO send new entry to server

    return false;
}

void Client::run() {
    // TODO read line from stdin
    std::string line;
    std::cout << "Make a query (add <name,address,phone>, select <name>) or just exit." << std::endl;
    std::cout << "> ";
    std::getline(std::cin, line);
    while (line != "exit") { // TODO sigint_handler.get_graceful_quit() == 0
        std::stringstream ss(line);
        std::string op;
        std::getline(ss, op, ' ');
        std::string arg;
        std::getline(ss, arg, '\n');

        if (op == "add") {
            if (add_entry(arg)) {
                std::cout << "Success" << std::endl;
            } else {
                std::cout << "Error" << std::endl;
            }
        } else if (op == "select"){
            if (get_entry(arg)) {
               std::cout << "Success" << std::endl;
            } else {
                std::cout << "Error" << std::endl;
            }
        } else {
            std::cout << "Invalid query, try again" << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, line);
    }
}