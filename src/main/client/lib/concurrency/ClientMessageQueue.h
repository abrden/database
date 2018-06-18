#ifndef DATABASE_CLIENTMESSAGEQUEUE_H
#define DATABASE_CLIENTMESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "ServerMessage.h"
#include "ClientMessage.h"
#include "MessageQueue.h"

class ClientMessageQueue {
    private:
        MessageQueue queue;
    public:
        ClientMessageQueue(const std::string& file, const char letter);
        int push(ClientMessageData data);
        ServerMessageData pop();
};


#endif //DATABASE_CLIENTMESSAGEQUEUE_H
