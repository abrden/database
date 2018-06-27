#ifndef DATABASE_ENTRYVALIDATOR_H
#define DATABASE_ENTRYVALIDATOR_H


#include <string>

class EntryValidator {
    public:
        static bool is_valid(const size_t name_size, const size_t address_size, const size_t phone_size);
};


#endif //DATABASE_ENTRYVALIDATOR_H
