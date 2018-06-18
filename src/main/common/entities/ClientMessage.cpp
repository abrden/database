#include "ClientMessage.h"

ClientMessage::ClientMessage(const long mtype, Query* query) : Message(mtype), query(query) {}

ClientMessage::~ClientMessage() {
    delete query;
}

ClientMessageData ClientMessage::serialize() {
    ClientMessageData cd;
    cd.mtype = get_mtype();
    cd.data = query->serialize();
    return cd;
}