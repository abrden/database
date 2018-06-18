#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>
#include <unistd.h>

#include "ClientMessageQueue.h"

ClientMessageQueue::ClientMessageQueue(const std::string& file, const char letter) {
    queue.attach(file, letter);
}

int ClientMessageQueue::push(ClientMessageData data) {
    return queue.push(&data, sizeof(data));
}

ServerMessageData ClientMessageQueue::pop() {
    ServerMessageData* data = (ServerMessageData*) queue.pop(getpid(), sizeof(ServerMessageData));
    return *data;
}
