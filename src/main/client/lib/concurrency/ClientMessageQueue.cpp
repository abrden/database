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

int ClientMessageQueue::push(ClientMessage& msg) const {
    ClientMessageData data = msg.serialize();
    return queue.push(&data, sizeof(data));
}

ServerMessage* ClientMessageQueue::pop(long mtype) const {
    ServerMessageData data;
    ssize_t received = queue.pop(&data, mtype, sizeof(ServerMessageData));
    if (received == 0) return nullptr;

    Response* response;
    if (data.data.operation == INSERT) {
        response = new Response(data.data.ok, data.data.msg, data.data.operation);
    } else if (data.data.operation == SELECT) {
        std::vector<Entry*> selection;
        for (size_t i = 0; i < data.data.len_selection; i++) {
            selection.push_back(new Entry(data.data.selection[i].name, data.data.selection[i].address, data.data.selection[i].phone));
        }
        response = new Response(data.data.ok, data.data.msg, data.data.operation, selection);
    }

    return new ServerMessage(data.mtype, response);
}
