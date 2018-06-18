#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <sys/types.h>

#include "ClientMessageQueue.h"

class Client {

    private:
        ClientMessageQueue queue;

        bool add_entry(std::string& name, std::string& address, std::string& phone);
        bool get_entry(std::string& name, std::string& address, std::string& phone);

    public:
        Client(const std::string& queue_file, const char queue_letter);
        void run();
        ~Client() = default;

};


#endif //DATABASE_CLIENT_H
