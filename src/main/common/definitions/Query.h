#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H

#include <string>

#include "EntryData.h"

enum QUERIES {
    GET_ENTRY,
    ADD_ENTRY
};

typedef struct {
    long mtype;
    int query;
    std::string name; // Esto podria ser un
    EntryData entry;   // union violento (?
} query;

#endif //DATABASE_QUERY_H