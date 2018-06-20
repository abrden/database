#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H

#include <string>
#include <stddef.h>

#include "Entry.h"

enum QUERY_TYPE {
    SELECT,
    INSERT
};

typedef struct {
    int operation;
    EntryData data;
} QueryData;

class Query {

    private:
        const int operation;
        const Entry entry;

    public:
        Query(const int operation, const std::string& name, const std::string& address, const std::string& phone);
        QueryData serialize() const;
        int get_operation() const;
        std::string get_name() const;
        std::string get_address() const;
        std::string get_phone() const;

};


#endif //DATABASE_QUERY_H
