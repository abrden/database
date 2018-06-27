#include "Query.h"

#include <cstring>
#include <sstream>

const static char SEPARATOR = ',';

// Client side
Query::Query(const int operation, const std::string& name, const std::string& address, const std::string& phone)
        : operation(operation), entry(name, address, phone),
          name_size(name.size()), address_size(address.size()), phone_size(phone.size()) {}

// Server side
Query::Query(const int operation, const std::string& name, const size_t name_size,
             const std::string& address, const size_t address_size,
             const std::string& phone, const size_t phone_size)
        : operation(operation), entry(name, address, phone),
          name_size(name_size), address_size(address_size), phone_size(phone_size) {}

size_t Query::get_name_size() const {
    return name_size;
}

size_t Query::get_address_size() const {
    return address_size;
}

size_t Query::get_phone_size() const {
    return phone_size;
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