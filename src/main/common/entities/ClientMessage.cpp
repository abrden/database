#include "ClientMessage.h"
#include <cstring>
#include <unistd.h>

ClientMessage::ClientMessage(const int sender_id, const Query& query) : Message(1), sender_id(sender_id), query(query) {}

ClientMessageData ClientMessage::serialize() const {
    ClientMessageData cm;
    memset(&cm, 0, sizeof(ClientMessageData));
    cm.mtype = get_mtype();
    cm.sender_id = sender_id;
    cm.data = query.serialize();
    return cm;
}

int ClientMessage::get_sender_id() const {
    return sender_id;
}

Query ClientMessage::get_query() const {
    return query;
}