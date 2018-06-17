#include "MessageQueue.h"

#include <sys/msg.h>
#include <string>
#include <cstring>
#include <cerrno>
#include <system_error>

int MessageQueue::push(QueryData* data) const {
    int sent = msgsnd(id, data, sizeof(QueryData) - sizeof(long), 0);
    if (sent < 0) {
        std::string message = std::string("Error in msgsnd(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message); 
    }
    return sent;
}

QueryData MessageQueue::pop(long msgtyp) const {
    QueryData data;
    ssize_t received = msgrcv(id, &data, sizeof(QueryData) - sizeof(long), msgtyp, 0);
    if (received < 0) {
        std::string message = std::string("Error in msgrcv(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message); 
    }
    return data;
}