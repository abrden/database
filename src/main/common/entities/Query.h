#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>

#include "QueryData.h"

class Query {

    private:
        int operation;
        std::string name;
        std::string address;
        std::string phone;

    public:
        Query(const int operation, const std::string& name, const std::string& address, const std::string& phone);
        explicit Query(std::string& entry_str);
        QueryData serialize() const;
        ~Query() = default;

};


#endif //DATABASE_ENTRY_H
