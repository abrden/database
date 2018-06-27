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
        const size_t name_size;
        const size_t address_size;
        const size_t phone_size;

    public:
        Query(const int operation, const std::string& name, const std::string& address, const std::string& phone);
        Query(const int operation, const std::string& name, const size_t name_size,
              const std::string& address, const size_t address_size,
              const std::string& phone, const size_t phone_size);
        QueryData serialize() const;
        int get_operation() const;
        std::string get_name() const;
        std::string get_address() const;
        std::string get_phone() const;
        size_t get_name_size() const;
        size_t get_address_size() const;
        size_t get_phone_size() const;

};


#endif //DATABASE_QUERY_H
