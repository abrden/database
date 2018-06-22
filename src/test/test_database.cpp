#include "Entry.h"
#include "Database.h"
#include "catch.hpp"

TEST_CASE("Database", "[db]") {

    Entry entry("Juan Perez", "Calle Falsa 123", "911");

    SECTION("entry_exists()") {
        Database db;

        REQUIRE_FALSE(db.entry_exists(&entry));
    }

    SECTION("insert_entry()") {
        Database db;
        db.insert_entry(&entry);

        REQUIRE(db.entry_exists(&entry));
    }
}