#ifndef DATABASE_SERVERMESSAGEQUEUE_H
#define DATABASE_SERVERMESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "MessageQueue.h"
#include "QueryData.h"

class ServerMessageQueue : public MessageQueue {

    public:
        ServerMessageQueue(const std::string& file, const char letter);
        explicit ServerMessageQueue(key_t key);
        ~ServerMessageQueue();
};


#endif //DATABASE_SERVERMESSAGEQUEUE_H
