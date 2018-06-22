#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <list>
#include <vector>

#include "DatabasePersister.h"
#include "Entry.h"

class Database {

    private:
        const std::string& db_file;
        std::list<Entry*> entries;

    public:
    Database(const std::string& db_file);
    bool entry_exists(const Entry* entry) const;
    void insert_entry(Entry* entry);
    std::vector<Entry*> select_entries(const Entry* entry) const;
    ~Database();
};


#endif //DATABASE_DATABASE_H
