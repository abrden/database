#ifndef DATABASE_ENTRYDATA_H
#define DATABASE_ENTRYDATA_H

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

#endif //DATABASE_ENTRYDATA_H
