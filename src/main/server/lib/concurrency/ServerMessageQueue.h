#ifndef DATABASE_SERVERMESSAGEQUEUE_H
#define DATABASE_SERVERMESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "ClientMessage.h"
#include "ServerMessage.h"
#include "MessageQueue.h"

class ServerMessageQueue {
    private:
        MessageQueue queue;

    public:
        ServerMessageQueue(const std::string& file, const char letter);
        int push(ServerMessage& msg) const;
        ClientMessage pop() const;
        ~ServerMessageQueue();
};


#endif //DATABASE_SERVERMESSAGEQUEUE_H
