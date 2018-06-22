#include "Entry.h"

#include <cstring>
#include <sstream>

const static char SEPARATOR = ',';

Entry::Entry(const std::string& name, const std::string& address, const std::string& phone)
        : name(name), address(address), phone(phone) {
    // TODO handle name > QUERY_BUFF_SIZE::NAME, etc
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

bool Entry::operator==(const Entry &e) const {
    return name == e.name && address == e.address && phone == e.phone;
}

bool Entry::weak_equals(const Entry &e) const {
    bool equals_name = e.name == "" ? true : name == e.name;
    bool equals_address = e.address == "" ? true : address == e.address;
    bool equals_phone = e.phone == "" ? true : phone == e.phone;
    return equals_name && equals_address && equals_phone;
}

EntryData Entry::serialize() const {
    EntryData e;
    memset(&e, 0, sizeof(EntryData));

    size_t len = name.copy(e.name, ENTRY_BUFF_SIZE::NAME, 0);
    e.name[len] = '\0';

    len = address.copy(e.address, ENTRY_BUFF_SIZE::ADDRESS, 0);
    e.address[len] = '\0';

    len = phone.copy(e.phone, ENTRY_BUFF_SIZE::PHONE, 0);
    e.phone[len] = '\0';
    
    return e;
}

std::string Entry::get_name() const {
    return name;
}

std::string Entry::get_address() const {
    return address;
}

std::string Entry::get_phone() const {
    return phone;
}

std::string Entry::to_string() const {
    std::stringstream ss;
    ss << name << SEPARATOR << address << SEPARATOR << phone << std::endl;
    return ss.str();
}
