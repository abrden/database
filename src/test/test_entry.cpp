#include <string.h>

#include "catch.hpp"
#include "Query.h"
#include "QueryData.h"

TEST_CASE("Query", "[entry]") {
    int query_type = QUERY_TYPE::GET;
    std::string name = "Osa Barbetta";
    std::string address = "El Bollo 123";
    std::string phone = "0800-OSA";
    Query entry(query_type, name, address, phone);

    QueryData entry_data = entry.serialize(0);

    REQUIRE(entry_data.query_type == query_type);
    REQUIRE(strcmp(entry_data.name, name.c_str()) == 0);
    REQUIRE(strcmp(entry_data.address, address.c_str()) == 0);
    REQUIRE(strcmp(entry_data.phone, phone.c_str()) == 0);
}