#include "Response.h"
#include <cstring>
#include <iostream>

Response::Response(const bool ok, const std::string& msg, const int operation)
        : ok(ok), operation(operation), msg(msg) {}

Response::Response(const bool ok, const std::string& msg, const int operation, const std::vector<Entry*>& selection)
        : ok(ok), operation(operation), msg(msg), selection(selection) {}

ResponseData Response::serialize() const {
    ResponseData r;
    memset(&r, 0, sizeof(ResponseData));
    r.ok = ok;
    r.operation = operation;
    size_t len = msg.copy(r.msg, RESPONSE_BUFF_SIZE::MSG, 0);
    r.msg[len] = '\0';
    r.len_selection = selection.size();

    for (size_t i = 0; i < r.len_selection; i++) {
        EntryData entry_i = selection[i]->serialize();
        memcpy(&r.selection[i], &entry_i, sizeof(EntryData));
    }


    return r;
}

bool Response::get_ok() const {
    return ok;
}

std::string Response::get_message() const {
    return msg;
}

std::vector<Entry*> Response::get_selection() const {
    return selection;
}

Response::~Response() {
    while (!selection.empty()) {
        delete selection.back();
        selection.pop_back();
    }
}

Response::Response(const Response& r) : ok(r.ok), operation(r.operation), msg(r.msg) {
    for (auto it = r.selection.begin(); it != r.selection.end(); ++it) {
        selection.push_back(new Entry((*it)->get_name(), (*it)->get_address(), (*it)->get_phone()));
    }
}
