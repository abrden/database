#ifndef DATABASE_MESSAGEQUEUE_H
#define DATABASE_MESSAGEQUEUE_H

#include <sys/types.h>

#include "EntryData.h"

class MessageQueue {

    private:
        int id;

    public:
        explicit MessageQueue(key_t key);
        int push(EntryData* data);
        EntryData pop();
        void destroy();
};


#endif //DATABASE_MESSAGEQUEUE_H
