#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <sys/types.h>
#include <list>

#include "ServerMessageQueue.h"
#include "Query.h"

class Server {

    private:
        std::string& file;
        ServerMessageQueue queue;
        std::list<Query*> entries;

        void entries_to_file();
        void add_entry(Query* entry);
        std::list<Query*> get_entry(std::string& name);

    public:
        Server(const std::string &queue_file, const char queue_letter, std::string db_file);
        void run();
        ~Server();

};

#endif //DATABASE_SERVER_H
