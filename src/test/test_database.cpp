#include "Entry.h"
#include "Database.h"
#include "catch.hpp"

TEST_CASE("Database", "[db]") {

    Entry entry("Juan Perez", "Calle Falsa 123", "911");

    SECTION("entry_exists() with empty db") {
        Database db;

        REQUIRE_FALSE(db.entry_exists(&entry));
    }

    SECTION("entry_exists() with entry in the db") {
        Database db;
        db.insert_entry(&entry);

        REQUIRE(db.entry_exists(&entry));
    }

    SECTION("insert_entry() with non-duplicate entry") {
        Database db;

        REQUIRE_NOTHROW(db.insert_entry(&entry));
    }

    SECTION("insert_entry() with duplicate entry") {
        Database db;
        db.insert_entry(&entry);

        REQUIRE_THROWS_AS(db.insert_entry(&entry), std::runtime_error);
    }

    SECTION("select_entries() with non-existent entry") {
        Database db;

        std::vector<Entry*> entries = db.select_entries(&entry);

        REQUIRE(entries.empty());
    }

//    SECTION("select_entries() with existent entry") {
//        Database db;
//        db.insert_entry(&entry);
//
//        std::vector entries = db.select_entries(&entry);
//
//        REQUIRE_FALSE(entries.empty());
//    }
}