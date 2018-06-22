#include <stdexcept>
#include "Database.h"
#include "Entry.h"

Database::Database(const std::string& db_file) : db_file(db_file) {
    DatabasePersister::load_from_file(db_file, entries);
}

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
    std::vector<Entry*> matching_entries;
    for (auto e : entries) {
        if (e->weak_equals(*entry)) {
            // TODO check if copying it's okay
            matching_entries.push_back(new Entry(*e));
        }
    }

    return matching_entries;
}

Database::~Database() {
    DatabasePersister::save_to_file(db_file, entries);
    for (auto e : entries) {
        delete e;
    }
}
