#include "Client.h"

#include <iostream>
#include <sstream>

Client::Client(key_t queue_key) : queue(queue_key) {}

bool Client::get_entry(std::string& name) {
    // TODO print matching entries
    std::string null_str = "";
    Entry entry(name, null_str, null_str);

    EntryData data = entry.serialize(MESSAGE_TYPE::GET);

    // lock()
    queue.push(&data);
    EntryData result = queue.pop();
    // unlock();
    return false;
}

bool Client::add_entry(std::string& entry_str) {
    Entry entry(entry_str);

    EntryData data = entry.serialize(MESSAGE_TYPE::ADD);
    queue.push(&data);

    return true;
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
            // Es necesario un lock??
            if (add_entry(arg)) {
                std::cout << "Success" << std::endl;
            } else {
                std::cout << "Error" << std::endl;
            }
        } else if (op == "select") {
            // Es necesario un lock??
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