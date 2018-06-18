#include "Query.h"

#include <sstream>

const static char SEPARATOR = ',';

Query::Query(const int operation, const std::string& name, const std::string& address, const std::string& phone)
        : operation(operation), name(name), address(address), phone(phone) {
            // TODO handle name > BUUFF_SIZE::NAME, etc
}

QueryData Query::serialize() const {
    QueryData qd;
    qd.operation = operation;

    size_t len = name.copy(qd.name, QUERY_BUFF_SIZE::NAME, 0);
    qd.name[len] = '\0';

    len = address.copy(qd.address, QUERY_BUFF_SIZE::ADDRESS, 0);
    qd.address[len] = '\0';

    len = phone.copy(qd.phone, QUERY_BUFF_SIZE::PHONE, 0);
    qd.phone[len] = '\0';
    
    return qd;
}