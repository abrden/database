#ifndef DATABASE_CLIENTMESSAGE_H
#define DATABASE_CLIENTMESSAGE_H

#include "Message.h"
#include "Query.h"

typedef struct {
    long mtype;
    QueryData data;
} ClientMessageData;

class ClientMessage : public Message {
    private:
        Query query;
    public:
        ClientMessage(long mtype, Query& query);
        ClientMessageData serialize() const;
        ~ClientMessage();
};


#endif //DATABASE_CLIENTMESSAGE_H
