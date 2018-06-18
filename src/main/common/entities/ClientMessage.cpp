#include <unistd.h>
#include "ClientMessage.h"

ClientMessage::ClientMessage(Query* query) : query(query) {}

ClientMessage::~ClientMessage() {
    delete query;
}

ClientMessageData ClientMessage::serialize() {
    ClientMessageData cd;
    cd.mtype = getpid();
    cd.data = query->serialize();
    return cd;
}