#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>

class Entry {

    private:
        const std::string name;
        const std::string address;
        const std::string phone;

    public:
        Entry(std::string& name, std::string& address, std::string& phone);
        ~Entry() = default;

};


#endif //DATABASE_ENTRY_H
