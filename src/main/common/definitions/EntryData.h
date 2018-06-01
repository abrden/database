#ifndef DATABASE_ENTRYDATA_H
#define DATABASE_ENTRYDATA_H

#include <stddef.h>

enum MESSAGE_TYPE {
    ADD = 1,
    GET
};

const static size_t NAME_SIZE = 62;
const static size_t ADDRESS_SIZE = 121;
const static size_t PHONE_SIZE = 14;

typedef struct {
    long mtype;
    char name[NAME_SIZE];
    char address[ADDRESS_SIZE];
    char phone[PHONE_SIZE];
} EntryData;

#endif //DATABASE_ENTRYDATA_H
