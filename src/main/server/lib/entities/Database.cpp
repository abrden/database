#include <stdexcept>
#include "Database.h"
#include "EntryValidator.h"
#include "Entry.h"

Database::Database(const std::string& db_file) : db_file(db_file) {
    DatabasePersister::load_from_file(db_file, entries);
}

bool Database::entry_exists(const std::string &name, const std::string &address, const std::string &phone) const {
    Entry entry(name, address, phone);
    for (auto e : entries) {
        if (*e == entry) return true;
    }
    return false;
}

void Database::insert_entry(const std::string& name, const size_t name_size,
                            const std::string& address, const size_t address_size,
                            const std::string& phone, const size_t phone_size) {
    if (entry_exists(name, address, phone)) {
        std::string message = "Error: Entry already exists in the database";
        throw std::runtime_error(message);
    } else {
        if (!EntryValidator::is_valid(name_size, address_size, phone_size)) {
            std::string message = "Error: Entry exceeds fields limits or is not valid";
            throw std::runtime_error(message);
        }
        auto entry_to_insert = new Entry(name, address, phone);
        entries.push_back(entry_to_insert);
    }
}

std::vector<Entry *> Database::select_entries(const std::string &name, const std::string &address, const std::string &phone) const {
    Entry entry(name, address, phone);
    std::vector<Entry*> matching_entries;
    for (auto e : entries) {
        if (e->matches(entry)) {
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
