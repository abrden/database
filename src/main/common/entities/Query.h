#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H

#include <string>
#include <stddef.h>

enum QUERY_TYPE {
    SELECT,
    INSERT
};

enum QUERY_BUFF_SIZE {
    NAME = 62,
    ADDRESS = 121,
    PHONE = 14
};

typedef struct {
    int operation;
    char name[QUERY_BUFF_SIZE::NAME];
    char address[QUERY_BUFF_SIZE::ADDRESS];
    char phone[QUERY_BUFF_SIZE::PHONE];
} QueryData;

class Query {

    private:
        int operation;
        std::string name;
        std::string address;
        std::string phone;

    public:
        Query(const int operation, const std::string& name, const std::string& address, const std::string& phone);
        QueryData serialize() const;
        int get_operation() const;
        std::string get_name() const;
        std::string get_address() const;
        std::string get_phone() const;

};


#endif //DATABASE_QUERY_H
