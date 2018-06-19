#ifndef DATABASE_SERVERMESSAGE_H
#define DATABASE_SERVERMESSAGE_H

#include "Message.h"
#include "Response.h"

typedef struct {
    long mtype;
    ResponseData data;
} ServerMessageData;

class ServerMessage : public Message {
    private:
        Response response;

    public:
        ServerMessage(const long mtype, const Response& response);
        ServerMessageData serialize() const;
        ~ServerMessage();
};


#endif //DATABASE_SERVERMESSAGE_H
