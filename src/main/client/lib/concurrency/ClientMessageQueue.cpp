#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>
#include <unistd.h>

#include "ServerMessage.h"
#include "ClientMessageQueue.h"

ClientMessageQueue::ClientMessageQueue(const std::string& file, const char letter) {
    queue.attach(file, letter);
}

int ClientMessageQueue::push(ClientMessage& msg) {
    ClientMessageData data = msg.serialize();
    return queue.push(&data, sizeof(data));
}

ServerMessage* ClientMessageQueue::pop(long mtype) {
    ServerMessageData data;
    queue.pop(&data, mtype, sizeof(ServerMessageData));
    Response response(data.data.ok, data.data.msg, data.data.operation);
    ServerMessage* msg = new ServerMessage(data.mtype, response);
    return msg;
}
