#include "Server.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <system_error>
#include <cstring>

Server::Server(const std::string& queue_file, const char queue_letter, std::string db_file)
        : file(db_file), queue(queue_file, queue_letter) {}

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

std::list<Query*> Server::get_entry(std::string& name) {
    // TODO
    std::list<Query*> l;
    return l;
}

void Server::add_entry(Query* entry) {
    entries.push_back(entry);
}

void Server::run() {
    // TODO read msgqueue queries
}

Server::~Server() {
    entries_to_file();
}