#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <sys/types.h>
#include <list>
#include <src/main/common/entities/Entry.h>

#include "ServerMessageQueue.h"
#include "Entry.h"

class Server {

    private:
        std::string& file;
        ServerMessageQueue queue;
        std::list<Entry*> entries;

        void entries_to_file();
        void add_entry(Entry* entry);
        std::list<Entry*> get_entry(std::string& name);

    public:
        Server(const std::string &queue_file, const char queue_letter, std::string db_file);
        void run();
        ~Server();

};

#endif //DATABASE_SERVER_H
