#include "Client.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Entry.h"
#include "Query.h"

Client::Client(const std::string &queue_file, const char queue_letter) : queue(queue_file, queue_letter) {}

bool Client::get_entry(const std::string& name, const std::string& address, const std::string& phone) {
    Query query(QUERY_TYPE::SELECT, name, address, phone);
    ClientMessage cmsg(getpid(), query);
    queue.push(cmsg);

    ServerMessage smsg = queue.pop(getpid());
    return smsg.get_response().get_ok();
}

bool Client::add_entry(const std::string& name, const std::string& address, const std::string& phone)  {
    Query query(QUERY_TYPE::INSERT, name, address, phone);
    ClientMessage cmsg(getpid(), query);
    queue.push(cmsg);

    ServerMessage smsg = queue.pop(getpid());
    return smsg.get_response().get_ok();
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
            Entry entry(arg);
            if (add_entry(entry.get_name(), entry.get_address(), entry.get_phone())) {
                std::cout << "Success" << std::endl;
            } else {
                std::cout << "Error" << std::endl;
            }
        } else if (op == "select") {
            // Es necesario un lock??
            Entry entry(arg);
            if (get_entry(entry.get_name(), entry.get_address(), entry.get_phone())) {
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