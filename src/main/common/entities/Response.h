#ifndef DATABASE_RESPONSE_H
#define DATABASE_RESPONSE_H

#include <string>

enum RESPONSE_BUFF_SIZE {
    MSG = 256
};

typedef struct {
    bool ok;
    int operation;
    char msg[RESPONSE_BUFF_SIZE::MSG];
} ResponseData;

class Response {
    private:
        const bool ok;
        const int operation;
        const std::string msg;

    public:
        Response(const bool ok, const std::string& msg, const int operation);
        ResponseData serialize() const;
};


#endif //DATABASE_RESPONSE_H
