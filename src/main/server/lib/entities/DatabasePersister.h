#ifndef DATABASE_DATABASEPERSISTER_H
#define DATABASE_DATABASEPERSISTER_H

#include <string>

#include "Database.h"
#include "Entry.h"

class DatabasePersister {
    public:
        static void save_to_file(const std::string& file, const std::list<Entry*>& entries);
        static void load_from_file(const std::string& file, std::list<Entry*>& entries);
};

#endif //DATABASE_DATABASEPERSISTER_H
