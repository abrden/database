#include <sys/types.h>
#include <sys/ipc.h>
#include <string>

#include "ServerMessageQueue.h"

ServerMessageQueue(const std::string& file, const char letter) {
    key_t key = ftok(file, letter);
    if ((id = msgget(key, 0777| IPC_CREAT)) < 0) {
        std::string message = std::string("Error in msgget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    };
}

