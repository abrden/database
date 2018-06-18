#include "MessageQueue.h"

#include <sys/msg.h>
#include <string>
#include <cstring>
#include <cerrno>
#include <system_error>

void MessageQueue::create(const std::string &file, const char letter) {
    key_t key = ftok(file.c_str(), letter);
    if ((id = msgget(key, 0777 | IPC_CREAT | IPC_EXCL)) < 0) {
        std::string message = std::string("Error in msgget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    };
}

void MessageQueue::attach(const std::string &file, const char letter) {
    key_t key = ftok(file.c_str(), letter);
    if ((id = msgget(key, 0777)) < 0) {
        std::string message = std::string("Error in msgget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    };
}

int MessageQueue::push(void* data, size_t data_size) const {
    int sent = msgsnd(id, data, data_size - sizeof(long), 0);
    if (sent < 0) {
        std::string message = std::string("Error in msgsnd(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message); 
    }
    return sent;
}

void* MessageQueue::pop(long msgtyp, size_t data_size) const {
    void* data;
    ssize_t received = msgrcv(id, &data, data_size - sizeof(long), msgtyp, 0);
    if (received < 0) {
        std::string message = std::string("Error in msgrcv(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message); 
    }
    return data;
}

void MessageQueue::destroy() {
    msgctl(id, IPC_RMID, nullptr);
}