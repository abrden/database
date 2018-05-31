#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <sys/types.h>
#include <list>

#include "MessageQueue.h"
#include "Entry.h"

class Server {

    private:
        std::string& file;
        MessageQueue queue; // Se destruye en el padre
        std::list<Entry*> entries;

        void entries_to_file();
        void add_entry(Entry* entry);
        std::list<Entry*> get_entry(std::string& name);

    public:
        Server(key_t queue_key, std::string file);
        void run();
        ~Server();

};

#endif //DATABASE_SERVER_H
