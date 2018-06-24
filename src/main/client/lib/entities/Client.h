#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <sys/types.h>

#include "ClientMessageQueue.h"
#include "SIGINTHandler.h"

class Client {

    private:
        ClientMessageQueue queue;
        SIGINTHandler sigint_handler;

        Response* insert_entry(const std::string &name, const std::string &address, const std::string &phone);
        Response* get_entry(const std::string& name, const std::string& address, const std::string& phone);

    public:
        Client(const std::string& queue_file, const char queue_letter);
        void run();
        ~Client();

};


#endif //DATABASE_CLIENT_H
