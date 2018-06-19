#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>

class Entry {
    private:
        std::string name;
        std::string address;
        std::string phone;
    public:
        Entry(const std::string& name, const std::string& address, const std::string& phone);
        Entry(std::string& entry_str);
        std::string get_name() const;
        std::string get_address() const;
        std::string get_phone() const;
        std::string to_string() const;
};


#endif //DATABASE_ENTRY_H
