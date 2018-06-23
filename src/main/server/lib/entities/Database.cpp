#include <stdexcept>
#include "Database.h"
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

void Database::insert_entry(const std::string &name, const std::string &address, const std::string &phone) {
    if (entry_exists(name, address, phone)) {
        std::string message = "Entry already exists";
        throw std::runtime_error(message);
    } else {
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
