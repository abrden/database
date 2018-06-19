#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>

#include "ServerMessageQueue.h"

ServerMessageQueue::ServerMessageQueue(const std::string& file, const char letter){
    queue.create(file, letter);
}

int ServerMessageQueue::push(ServerMessage& msg) const {
    ServerMessageData data = msg.serialize();
    return queue.push(&data, sizeof(data));
}

ClientMessage ServerMessageQueue::pop() const {
    ClientMessageData data;
    queue.pop(&data, 0, sizeof(ClientMessageData));
    Query query(data.data.operation, data.data.name, data.data.address, data.data.phone);
    ClientMessage msg(data.mtype, query);
    return msg;
}

ServerMessageQueue::~ServerMessageQueue() {
    queue.destroy();
}

