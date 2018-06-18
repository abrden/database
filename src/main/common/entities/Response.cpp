#include "Response.h"

Response::Response(const bool ok, const std::string& msg, const int operation)
        : ok(ok), operation(operation), msg(msg){}

ResponseData Response::serialize() const {
    ResponseData data;
    data.ok = ok;
    data.operation = operation;
    size_t len = msg.copy(data.msg, RESPONSE_BUFF_SIZE::MSG, 0);
    data.msg[len] = '\0';
    return data;
}