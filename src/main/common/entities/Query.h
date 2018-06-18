#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H

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
        QueryData serialize() const;

};


#endif //DATABASE_QUERY_H
