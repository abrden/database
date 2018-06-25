#ifndef DATABASE_CLIENTMESSAGE_H
#define DATABASE_CLIENTMESSAGE_H

#include "Message.h"
#include "Query.h"

typedef struct {
    long mtype;
    int sender_id;
    QueryData data;
} ClientMessageData;

class ClientMessage : public Message {
    private:
        const int sender_id;
        Query query;
    public:
        ClientMessage(const int sender_id, const Query& query);
        ClientMessageData serialize() const;
        int get_sender_id() const;
        Query get_query() const;
};


#endif //DATABASE_CLIENTMESSAGE_H
