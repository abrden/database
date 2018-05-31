#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <sys/types.h>

#include "Entry.h"
#include "MessageQueue.h"

class Client {

    private:
        MessageQueue queue; // Se destruye en el padre

        bool add_entry(std::string& entry_str);
        bool get_entry(std::string& name);

    public:
        Client(key_t queue_key);
        void run();
        ~Client() = default;

};


#endif //DATABASE_CLIENT_H
