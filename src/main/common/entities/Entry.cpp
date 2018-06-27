#include "Entry.h"

#include <cstring>
#include <sstream>
#include <algorithm>

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

bool Entry::matches(const Entry &e) const {
    std::string e1_name = name;
    std::string e1_address = address;
    std::string e1_phone = phone;
    std::string e2_name = e.name;
    std::string e2_address = e.address;
    std::string e2_phone = e.phone;

    std::transform(e1_name.begin(), e1_name.end(), e1_name.begin(), ::tolower);
    std::transform(e1_address.begin(), e1_address.end(), e1_address.begin(), ::tolower);
    std::transform(e1_phone.begin(), e1_phone.end(), e1_phone.begin(), ::tolower);
    std::transform(e2_name.begin(), e2_name.end(), e2_name.begin(), ::tolower);
    std::transform(e2_address.begin(), e2_address.end(), e2_address.begin(), ::tolower);
    std::transform(e2_phone.begin(), e2_phone.end(), e2_phone.begin(), ::tolower);

    bool equals_name = e2_name == "" ? true : e1_name == e2_name;
    bool equals_address = e2_address == "" ? true : e1_address == e2_address;
    bool equals_phone = e2_phone == "" ? true : e1_phone == e2_phone;
    return equals_name && equals_address && equals_phone;
}

EntryData Entry::serialize() const {
    EntryData e;
    memset(&e, 0, sizeof(EntryData));

    size_t len = name.copy(e.name, ENTRY_BUFF_SIZE::NAME, 0);
    e.name[len] = '\0';
    e.name_size = name.size();

    len = address.copy(e.address, ENTRY_BUFF_SIZE::ADDRESS, 0);
    e.address[len] = '\0';
    e.address_size = address.size();

    len = phone.copy(e.phone, ENTRY_BUFF_SIZE::PHONE, 0);
    e.phone[len] = '\0';
    e.phone_size = phone.size();

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

std::ostream &operator<<(std::ostream &os, const Entry &entry) {
    return os << entry.name << SEPARATOR << entry.address << SEPARATOR << entry.phone;
}
