#include "ClientMessage.h"
#include <cstring>
#include <unistd.h>

ClientMessage::ClientMessage(long mtype, const Query& query) : Message(mtype), query(query) {}

ClientMessageData ClientMessage::serialize() const {
    ClientMessageData cm;
    memset(&cm, 0, sizeof(ClientMessageData));
    cm.mtype = get_mtype();
    cm.data = query.serialize();
    return cm;
}

Query ClientMessage::get_query() const {
    return query;
}