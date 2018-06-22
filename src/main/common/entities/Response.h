#ifndef DATABASE_RESPONSE_H
#define DATABASE_RESPONSE_H

#include <string>
#include <vector>

#include "Entry.h"

enum RESPONSE_BUFF_SIZE {
    MSG = 60,
    SELECTION = 32
};

typedef struct {
    bool ok;
    int operation;
    char msg[RESPONSE_BUFF_SIZE::MSG];
    size_t len_selection;
    EntryData selection[RESPONSE_BUFF_SIZE::SELECTION];
} ResponseData;

class Response {
    private:
        const bool ok;
        const int operation;
        const std::string msg;
        std::vector<Entry*> selection;

    public:
        Response(const bool ok, const std::string& msg, const int operation);
        Response(const bool ok, const std::string& msg, const int operation, const std::vector<Entry*>& selection);
        Response(const Response& r);
        ResponseData serialize() const;
        bool get_ok() const;
        std::vector<Entry*> get_selection() const;
        ~Response();
};


#endif //DATABASE_RESPONSE_H
