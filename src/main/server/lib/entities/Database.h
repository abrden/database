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
    void insert_entry(const std::string& name, const size_t name_size,
                      const std::string& address, const size_t address_size,
                      const std::string& phone, const size_t phone_size);
    std::vector<Entry*> select_entries(const std::string &name, const std::string &address, const std::string &phone) const;
    ~Database();
};


#endif //DATABASE_DATABASE_H
