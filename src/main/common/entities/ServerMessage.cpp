#include "ServerMessage.h"

ServerMessage::ServerMessage(const long mtype, Response* response)
        : Message(mtype), response(response) {}

ServerMessage::~ServerMessage() {
    delete response;
}

ServerMessageData ServerMessage::serialize() const {
    ServerMessageData sm;
    sm.mtype = get_mtype();
    sm.data = response->serialize();

    return sm;
}