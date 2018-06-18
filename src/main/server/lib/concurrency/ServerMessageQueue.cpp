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

ClientMessageData ServerMessageQueue::pop() {
    ClientMessageData* data =  (ClientMessageData*) queue.pop(0, sizeof(ClientMessageData));
    return *data;
}

ServerMessageQueue::~ServerMessageQueue() {
    queue.destroy();
}

