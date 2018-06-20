#include "Response.h"
#include <cstring>

Response::Response(const bool ok, const std::string& msg, const int operation)
        : ok(ok), operation(operation), msg(msg) {}

Response::Response(const bool ok, const std::string& msg, const int operation, const std::vector<Entry*>& entries)
        : ok(ok), operation(operation), msg(msg), entries(entries) {}

ResponseData Response::serialize() const {
    ResponseData r;
    memset(&r, 0, sizeof(ResponseData));
    r.ok = ok;
    r.operation = operation;
    size_t len = msg.copy(r.msg, RESPONSE_BUFF_SIZE::MSG, 0);
    r.msg[len] = '\0';
    r.len_selection = entries.size();

    EntryData raw_entries[RESPONSE_BUFF_SIZE::SELECTION];
    for (size_t i = 0; i < r.len_selection; i++) {
        raw_entries[i] = entries[i]->serialize();
    }
    memcpy(r.selection, raw_entries, r.len_selection);
    return r;
}

bool Response::get_ok() const {
    return ok;
}