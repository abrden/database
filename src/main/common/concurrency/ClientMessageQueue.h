#ifndef DATABASE_CLIENTMESSAGEQUEUE_H
#define DATABASE_CLIENTMESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "MessageQueue.h"
#include "QueryData.h"

class ClientMessageQueue : public MessageQueue {
    public:
        ClientMessageQueue(const std::string& file, const char letter);
        explicit ClientMessageQueue(key_t key);
};


#endif //DATABASE_CLIENTMESSAGEQUEUE_H
