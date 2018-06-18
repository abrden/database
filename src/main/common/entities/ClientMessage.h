#ifndef DATABASE_CLIENTMESSAGE_H
#define DATABASE_CLIENTMESSAGE_H

#include "Message.h"
#include "Query.h"
#include "QueryData.h"

typedef struct {
    long mtype;
    QueryData data;
} ClientMessageData;

class ClientMessage {
    private:
        Query* query;
    public:
        explicit ClientMessage(Query* query);
        ClientMessageData serialize();
        ~ClientMessage();
};


#endif //DATABASE_CLIENTMESSAGE_H
