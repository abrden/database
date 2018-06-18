#include "Response.h"
#include <cstring>

Response::Response(const bool ok, const std::string& msg, const int operation)
        : ok(ok), operation(operation), msg(msg){}

ResponseData Response::serialize() const {
    ResponseData r;
    memset(&r, 0, sizeof(ResponseData));
    r.ok = ok;
    r.operation = operation;
    size_t len = msg.copy(r.msg, RESPONSE_BUFF_SIZE::MSG, 0);
    r.msg[len] = '\0';
    return r;
}