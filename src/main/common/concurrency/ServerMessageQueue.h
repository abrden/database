#ifndef DATABASE_SERVERMESSAGEQUEUE_H
#define DATABASE_SERVERMESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "MessageQueue.h"
#include "QueryData.h"

class ServerMessageQueue : public MessageQueue {

    private:
        int id;

    public:
        ServerMessageQueue(const std::string& file, const char letter);
        explicit ServerMessageQueue(key_t key);
        int push(QueryData* data);
        virtual QueryData pop();
        virtual ~ServerMessageQueue();
};


#endif //DATABASE_SERVERMESSAGEQUEUE_H
