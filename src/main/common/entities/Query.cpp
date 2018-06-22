#include "Query.h"

#include <cstring>
#include <sstream>

const static char SEPARATOR = ',';

Query::Query(const int operation, const std::string& name, const std::string& address, const std::string& phone)
        : operation(operation), entry(name, address, phone) {
            // TODO handle name > BUUFF_SIZE::NAME, etc
}

QueryData Query::serialize() const {
    QueryData q;
    memset(&q, 0, sizeof(QueryData));

    q.operation = operation;
    q.data = entry.serialize();
    
    return q;
}

int Query::get_operation() const {
    return operation;
}

std::string Query::get_name() const {
    return entry.get_name();
}

std::string Query::get_address() const {
    return entry.get_address();
}

std::string Query::get_phone() const {
    return entry.get_phone();
}