#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>

#include "ClientMessageQueue.h"

ClientMessageQueue::ClientMessageQueue(const std::string &file, const char letter){
    key_t key = ftok(file.c_str(), letter);
    if ((id = msgget(key, 0777)) < 0) {
        std::string message = std::string("Error in msgget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    };
}

ClientMessageQueue::ClientMessageQueue(key_t key) {
    if ((id = msgget(key, 0777)) < 0) {
        std::string message = std::string("Error in msgget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    };
}