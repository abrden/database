#include <string.h>

#include "catch.hpp"
#include "Entry.h"
#include "EntryData.h"

TEST_CASE("Entry", "[entry]") {
    std::string name = "Osa Barbetta";
    std::string address = "El Bollo 123";
    std::string phone = "0800-OSA";
    Entry entry(name, address, phone);

    EntryData entry_data = entry.serialize(0);

    REQUIRE(strcmp(entry_data.name, name.c_str()) == 0);
    REQUIRE(strcmp(entry_data.address, address.c_str()) == 0);
    REQUIRE(strcmp(entry_data.phone, phone.c_str()) == 0);
}