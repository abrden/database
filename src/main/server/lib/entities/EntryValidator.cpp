#include "EntryValidator.h"
#include "Entry.h"

bool EntryValidator::is_valid(const size_t name_size, const size_t address_size, const size_t phone_size) {
    return (name_size <= ENTRY_BUFF_SIZE::NAME - 1 &&
            address_size <= ENTRY_BUFF_SIZE::ADDRESS - 1 &&
            phone_size <= ENTRY_BUFF_SIZE::PHONE - 1);

    // TODO See if more validations are needed
}