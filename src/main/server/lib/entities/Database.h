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
    bool entry_exists(const std::string &name, const std::string &address, const std::string &phone) const;
    void insert_entry(const std::string &name, const std::string &address, const std::string &phone);
    std::vector<Entry*> select_entries(const std::string &name, const std::string &address, const std::string &phone) const;
    ~Database();
};


#endif //DATABASE_DATABASE_H
