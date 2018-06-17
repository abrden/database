#ifndef DATABASE_MESSAGEQUEUE_H
#define DATABASE_MESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

#include "QueryData.h"

class MessageQueue {

    protected:
        int id;

    public:
        int push(QueryData* data) const;
        QueryData pop(long msgtyp = 0) const;
};


#endif //DATABASE_MESSAGEQUEUE_H
