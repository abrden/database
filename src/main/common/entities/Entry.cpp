#include "Entry.h"

#include <sstream>

Entry::Entry(std::string& name, std::string& address, std::string& phone)
        : name(name), address(address), phone(phone) {}

std::string Entry::to_string() const {
    std::stringstream ss;
    ss << name << "," << address << "," << phone << std::endl;
    return ss.str();
}