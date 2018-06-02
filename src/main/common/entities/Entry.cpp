#include "Entry.h"

#include <sstream>
#include <src/main/common/definitions/QueryData.h>
#include "QueryData.h"

const static char SEPARATOR = ',';

Entry::Entry(int query_type, std::string& name, std::string& address, std::string& phone)
        : query_type(query_type), name(name), address(address), phone(phone) {
            // TODO handle name > BUUFF_SIZE::NAME, etc
}

Entry::Entry(std::string& entry_str) {
    std::stringstream ss(entry_str);
    std::string arg;

    std::getline(ss, arg, SEPARATOR);
    name = arg;
    std::getline(ss, arg, SEPARATOR);
    address = arg;
    std::getline(ss, arg, SEPARATOR);
    phone = arg;
}

std::string Entry::to_string() const {
    std::stringstream ss;
    ss << name << SEPARATOR << address << SEPARATOR << phone << std::endl;
    return ss.str();
}

QueryData Entry::serialize(long type) const {
    QueryData data;
    data.query_type = query_type;
    data.mtype = type;

    size_t len = name.copy(data.name, BUFF_SIZE::NAME, 0);
    data.name[len] = '\0';

    len = address.copy(data.address, BUFF_SIZE::ADDRESS, 0);
    data.address[len] = '\0';

    len = phone.copy(data.phone, BUFF_SIZE::PHONE, 0);
    data.phone[len] = '\0';
    
    return data;
}