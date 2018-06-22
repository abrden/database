#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <sys/types.h>
#include <list>

#include "Database.h"
#include "ServerMessageQueue.h"
#include "Entry.h"
#include "SIGINTHandler.h"

class Server {

    private:
        Database db;
        std::string& file;

        ServerMessageQueue queue;
        SIGINTHandler sigint_handler;

        std::list<Entry*> entries;

        void entries_to_file();
        Response* insert_entry(const std::string& name, const std::string& address, const std::string& phone);
        Response* select_entries(const std::string& name, const std::string& address, const std::string& phone) const;

    public:
        Server(const std::string &queue_file, const char queue_letter, std::string db_file);
        void run();
        ~Server();

};

#endif //DATABASE_SERVER_H
