#include "ClientMessage.h"
#include <cstring>
#include <unistd.h>

ClientMessage::ClientMessage(Query* query) : query(query) {}

ClientMessage::~ClientMessage() {
    delete query;
}

ClientMessageData ClientMessage::serialize() const {
    ClientMessageData cm;
    memset(&cm, 0, sizeof(ClientMessageData));
    cm.mtype = getpid();
    cm.data = query->serialize();
    return cm;
}