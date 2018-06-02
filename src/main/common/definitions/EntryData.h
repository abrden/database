#ifndef DATABASE_ENTRYDATA_H
#define DATABASE_ENTRYDATA_H

#include <stddef.h>

enum BUFF_SIZE {
    NAME = 62,
    ADDRESS = 121,
    PHONE = 14
};

typedef struct {
    long mtype;
    char name[BUFF_SIZE::NAME];
    char address[BUFF_SIZE::ADDRESS];
    char phone[BUFF_SIZE::PHONE];
} EntryData;

#endif //DATABASE_ENTRYDATA_H
