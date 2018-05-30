#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <sys/types.h>
#include <list>

#include "MessageQueue.h"
#include "Entry.h"

class Server {

    private:
        std::string file;
        MessageQueue queue; // Se destruye en el padre
        std::list<Entry> entries;

    public:
        Server(key_t queue_key, std::string& file);
        void entries_to_file();
        ~Server() = default;

};

#endif //DATABASE_SERVER_H
