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

    SECTION("select_entries() with existent entry") {
        Database db;
        db.insert_entry(&entry);

        std::vector<Entry*> entries = db.select_entries(&entry);

        REQUIRE_FALSE(entries.empty());
        Entry* matching_entry = entries.at(0);
        REQUIRE(*matching_entry == entry);

        delete entries[0];
    }

    SECTION("select_entries() with wildcards") {
        Database db;
        Entry entry_2("Juan Perez", "Balcarce 950", "0800-4444");
        db.insert_entry(&entry);
        db.insert_entry(&entry_2);
        Entry query_entry("Juan Perez", "", "");

        std::vector<Entry*> entries = db.select_entries(&query_entry);

        REQUIRE_FALSE(entries.empty());
        Entry* matching_entry_1 = entries.at(0);
        Entry* matching_entry_2 = entries.at(1);
        REQUIRE(*matching_entry_1 == entry);
        REQUIRE(*matching_entry_2 == entry_2);

        delete entries.at(0);
        delete entries.at(1);
    }
}