#include "Entry.h"
#include "Database.h"
#include "catch.hpp"

TEST_CASE("Database", "[db]") {

    const std::string db_file = "/tmp/test_db";
    const std::string name = "Juan Perez";
    const std::string address = "Calle Falsa 123";
    const std::string phone = "911";
    Entry entry(name, address, phone);

    SECTION("entry_exists() with empty db") {
        Database db(db_file);

        REQUIRE_FALSE(db.entry_exists(name, address, phone));
    }

    SECTION("entry_exists() with entry in the db") {
        Database db(db_file);
        db.insert_entry(name, address, phone);

        REQUIRE(db.entry_exists(name, address, phone));
    }

    SECTION("insert_entry() with non-duplicate entry") {
        Database db(db_file);

        REQUIRE_NOTHROW(db.insert_entry(name, address, phone));
    }

    SECTION("insert_entry() with duplicate entry") {
        Database db(db_file);
        db.insert_entry(name, address, phone);

        REQUIRE_THROWS_AS(db.insert_entry(name, address, phone), std::runtime_error);
    }

    SECTION("select_entries() with non-existent entry") {
        Database db(db_file);

        std::vector<Entry*> entries = db.select_entries(name, address, phone);

        REQUIRE(entries.empty());
    }

    SECTION("select_entries() with existent entry") {
        Database db(db_file);
        db.insert_entry(name, address, phone);

        std::vector<Entry*> entries = db.select_entries(name, address, phone);

        REQUIRE_FALSE(entries.empty());
        Entry* matching_entry = entries.at(0);
        REQUIRE(*matching_entry == entry);

        delete entries[0];
    }

    SECTION("select_entries() with wildcards") {
        Database db(db_file);
        const std::string name_2 = "Juan Perez";
        const std::string address_2 = "Balcarce 950";
        const std::string phone_2 = "0800-4444";
        Entry entry_2(name_2, address_2, phone_2);
        db.insert_entry(name, address, phone);
        db.insert_entry(name_2, address_2, phone_2);

        std::vector<Entry*> entries = db.select_entries(name, "", "");

        REQUIRE_FALSE(entries.empty());
        Entry* matching_entry_1 = entries.at(0);
        Entry* matching_entry_2 = entries.at(1);
        REQUIRE(*matching_entry_1 == entry);
        REQUIRE(*matching_entry_2 == entry_2);

        delete entries.at(0);
        delete entries.at(1);
    }
}