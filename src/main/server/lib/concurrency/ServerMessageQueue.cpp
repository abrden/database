#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>
#include <src/main/common/entities/ClientMessage.h>

#include "ServerMessageQueue.h"

ServerMessageQueue::ServerMessageQueue(const std::string& file, const char letter){
    queue.create(file, letter);
}

int ServerMessageQueue::push(ServerMessage& msg) const {
    ServerMessageData data = msg.serialize();
    return queue.push(&data, sizeof(data));
}

ClientMessage* ServerMessageQueue::pop() const {
    ClientMessageData data;
    ssize_t received = queue.pop(&data, 0, sizeof(ClientMessageData));
    if (received == 0) {
        return nullptr;
    }
    Query query(data.data.operation, data.data.data.name, data.data.data.address, data.data.data.phone);
    return new ClientMessage(data.sender_id, query);
}

ServerMessageQueue::~ServerMessageQueue() {
    queue.destroy();
}

