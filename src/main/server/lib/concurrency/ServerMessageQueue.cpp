#include <sys/types.h>
#include <sys/ipc.h>
#include <string>
#include <sys/msg.h>
#include <system_error>
#include <cstring>
#include <src/main/common/entities/ClientMessage.h>
#include <src/main/common/definitions/QueryData.h>

#include "ServerMessageQueue.h"

ServerMessageQueue::ServerMessageQueue(const std::string& file, const char letter){
    queue.create(file, letter);
}

ClientMessage* ServerMessageQueue::pop() {
    ClientMessageData* data =  (ClientMessageData*) queue.pop(0, sizeof(ClientMessageData));
    Query* query = new Query(data->data.operation, data->data.name, data->data.address, data->data.phone);
    ClientMessage* msg = new ClientMessage(data->mtype, query);
    return msg;
}

ServerMessageQueue::~ServerMessageQueue() {
    queue.destroy();
}

