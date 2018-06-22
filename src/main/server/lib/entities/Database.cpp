#include "Database.h"

Database::Database() {}

bool Database::entry_exists(const Entry *entry) const {
    return false;
}

void Database::insert_entry(const Entry *entry) {

}

std::vector<Entry *> Database::select_entries(const Entry *entry) const {
    return std::vector<Entry *>();
}

Database::~Database() {

}
