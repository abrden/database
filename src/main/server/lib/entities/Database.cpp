#include <stdexcept>
#include "Database.h"
#include "Entry.h"

Database::Database() {}

bool Database::entry_exists(const Entry *entry) const {
    for (auto e : entries) {
        if (*e == *entry) {
            return true;
        }
    }
    return false;
}

void Database::insert_entry(Entry *entry) {
    if (entry_exists(entry)) {
        std::string message = "Error in insert_entry(): Entry exists";
        throw std::runtime_error(message);
    } else {
        // TODO check if we should insert the received entry or create a copy of it
        Entry* entry_to_insert = new Entry(*entry);
        entries.push_back(entry_to_insert);
    }
}

std::vector<Entry *> Database::select_entries(const Entry *entry) const {
    return std::vector<Entry *>();
}

Database::~Database() {
    for (auto e : entries) {
        delete e;
    }
}
