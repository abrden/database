#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>

#include "EntryData.h"

class Entry {

    private:
        int query_type;
        std::string name;
        std::string address;
        std::string phone;

    public:
        Entry(int query_type, std::string& name, std::string& address, std::string& phone);
        Entry(std::string& entry_str);
        std::string to_string() const;
        EntryData serialize(long type) const;
        ~Entry() = default;

};


#endif //DATABASE_ENTRY_H
