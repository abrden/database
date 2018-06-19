#include "ServerMessage.h"
#include <cstring>

ServerMessage::ServerMessage(const long mtype, Response& response)
        : Message(mtype), response(response) {}

ServerMessage::~ServerMessage() {
//    delete response;
}

ServerMessageData ServerMessage::serialize() const {
    ServerMessageData sm;
    memset(&sm, 0, sizeof(ServerMessageData));
    sm.mtype = get_mtype();
    sm.data = response.serialize();

    return sm;
}