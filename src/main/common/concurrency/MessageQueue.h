#ifndef DATABASE_MESSAGEQUEUE_H
#define DATABASE_MESSAGEQUEUE_H

#include <sys/types.h>
#include <string>

class MessageQueue {

    private:
        int id;

    public:
        void create(const std::string &file, const char letter);
        void attach(const std::string &file, const char letter);
        int push(void* data, size_t data_size) const;
        void* pop(long msgtyp, size_t data_size) const;
        void destroy();
};


#endif //DATABASE_MESSAGEQUEUE_H
