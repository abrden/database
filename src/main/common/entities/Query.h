#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>

#include "QueryData.h"

class Query {

    private:
        int query_type;
        std::string name;
        std::string address;
        std::string phone;

    public:
        Query(int query_type, std::string& name, std::string& address, std::string& phone);
        Query(std::string& entry_str);
        std::string to_string() const;
        QueryData serialize(long type) const;
        ~Query() = default;

};


#endif //DATABASE_ENTRY_H
