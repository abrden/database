#include "Query.h"

#include <cstring>
#include <sstream>

const static char SEPARATOR = ',';

Query::Query(const int operation, const std::string& name, const std::string& address, const std::string& phone)
        : operation(operation), name(name), address(address), phone(phone) {
            // TODO handle name > BUUFF_SIZE::NAME, etc
}

QueryData Query::serialize() const {
    QueryData q;
    memset(&q, 0, sizeof(QueryData));

    q.operation = operation;

    size_t len = name.copy(q.name, QUERY_BUFF_SIZE::NAME, 0);
    q.name[len] = '\0';

    len = address.copy(q.address, QUERY_BUFF_SIZE::ADDRESS, 0);
    q.address[len] = '\0';

    len = phone.copy(q.phone, QUERY_BUFF_SIZE::PHONE, 0);
    q.phone[len] = '\0';
    
    return q;
}

int Query::get_operation() const {
    return operation;
}

std::string Query::get_name() const {
    return name;
}

std::string Query::get_address() const {
    return address;
}

std::string Query::get_phone() const {
    return phone;
}