#ifndef DATABASE_ENTRYDATA_H
#define DATABASE_ENTRYDATA_H

#include <stddef.h>

const static size_t NAME_SIZE = 61;
const static size_t ADDRESS_SIZE = 120;
const static size_t PHONE_SIZE = 13;

typedef struct {
    long mtype;
    char name[NAME_SIZE];
    char address[ADDRESS_SIZE];
    char phone[PHONE_SIZE];
} EntryData;

#endif //DATABASE_ENTRYDATA_H
