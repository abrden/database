#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <sys/types.h>
#include <list>

#include "ServerMessageQueue.h"
#include "Query.h"

class Server {

    private:
        std::string& file;
        ServerMessageQueue queue; // Se destruye en el padre
        std::list<Query*> entries;

        void entries_to_file();
        void add_entry(Query* entry);
        std::list<Query*> get_entry(std::string& name);

    public:
        Server(key_t queue_key, std::string file);
        void run();
        ~Server();

};

#endif //DATABASE_SERVER_H
