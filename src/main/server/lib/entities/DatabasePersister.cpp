#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <system_error>

#include "DatabasePersister.h"

void DatabasePersister::save_to_file(const std::string& file, const std::list<Entry*>& entries) {
    // TODO check errors in opening of file
    int fd = open(file.c_str(), O_WRONLY | O_CREAT, 0666);

    for (auto const& entry : entries) {
        std::string entry_str = entry->to_string();
        std::cout << "Writing to file : " << entry_str;
        ssize_t bytes_written = write(fd, entry_str.c_str(), entry_str.size());
        if ((unsigned long) bytes_written != entry_str.size()) {
            close(fd);

            std::string message = std::string("Error in write: could not write db file: ") + std::string(strerror(errno));
            throw std::system_error(errno, std::system_category(), message);
        }
    }

    close(fd);
}

void DatabasePersister::load_from_file(const std::string& file, std::list<Entry*>& entries) {
    // TODO implement
    return;
}
