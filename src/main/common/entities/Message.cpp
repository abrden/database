#include "Message.h"

Message::Message(long mtype) : mtype(mtype) {}

long Message::get_mtype() {
    return mtype;
}