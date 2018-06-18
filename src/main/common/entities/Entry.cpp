#include "Entry.h"

#include <sstream>

const static char SEPARATOR = ',';

Entry::Entry(std::string& name, std::string& address, std::string& phone)
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

std::string& Entry::get_name() {
    return name;
}

std::string& Entry::get_address() {
    return address;
}

std::string& Entry::get_phone() {
    return phone;
}

std::string Entry::to_string() const {
    std::stringstream ss;
    ss << name << SEPARATOR << address << SEPARATOR << phone << std::endl;
    return ss.str();
}
