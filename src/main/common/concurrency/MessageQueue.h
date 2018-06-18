#ifndef DATABASE_MESSAGEQUEUE_H
#define DATABASE_MESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "QueryData.h"

class MessageQueue {

    protected:
        int id;

        QueryData pop(long msgtyp) const;
    public:
        int push(QueryData* data) const;
        virtual QueryData pop() = 0;
};


#endif //DATABASE_MESSAGEQUEUE_H
