#include "ClientMessage.h"
#include <cstring>
#include <unistd.h>

ClientMessage::ClientMessage(long mtype, Query& query) : Message(mtype), query(query) {}

ClientMessage::~ClientMessage() {
//    delete query;
}

ClientMessageData ClientMessage::serialize() const {
    ClientMessageData cm;
    memset(&cm, 0, sizeof(ClientMessageData));
    cm.mtype = get_mtype();
    cm.data = query.serialize();
    return cm;
}