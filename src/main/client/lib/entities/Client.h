#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <sys/types.h>

#include "Query.h"
#include "ClientMessageQueue.h"

class Client {

    private:
        ClientMessageQueue queue;

        bool add_entry(std::string& entry_str);
        bool get_entry(std::string& name);

    public:
        Client(const std::string& queue_file, const char queue_letter);
        void run();
        ~Client() = default;

};


#endif //DATABASE_CLIENT_H
