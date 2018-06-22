#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>
#include <iostream>

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
    std::cout << "Receiving msg with name: " << data.data.data.name << ", address: " << data.data.data.address << ", phone: " << data.data.data.phone << std::endl;
    Query query(data.data.operation, data.data.data.name, data.data.data.address, data.data.data.phone);
    return new ClientMessage(data.mtype, query);
}

ServerMessageQueue::~ServerMessageQueue() {
    queue.destroy();
}

