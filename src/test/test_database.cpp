#include "Entry.h"
#include "Database.h"
#include "catch.hpp"

TEST_CASE("Database", "[db]") {

    const std::string name = "Juan Perez";
    const std::string address = "Calle Falsa 123";
    const std::string phone = "911";
    Entry entry(name, address, phone);

    SECTION("entry_exists() with empty db") {
        const std::string db_file = "/tmp/test_db_1"
        Database db(db_file);

        REQUIRE_FALSE(db.entry_exists(name, address, phone));
    }

    SECTION("entry_exists() with entry in the db") {
        const std::string db_file = "/tmp/test_db_2"
        Database db(db_file);
        db.insert_entry(name, name.size(), address, address.size(), phone, phone.size());

        REQUIRE(db.entry_exists(name, address, phone));
    }

    SECTION("insert_entry() with non-duplicate entry") {
        const std::string db_file = "/tmp/test_db_3"
        Database db(db_file);

        REQUIRE_NOTHROW(db.insert_entry(name, name.size(), address, address.size(), phone, phone.size()));
    }

    SECTION("insert_entry() with duplicate entry") {
        const std::string db_file = "/tmp/test_db_4"
        Database db(db_file);
        db.insert_entry(name, name.size(), address, address.size(), phone, phone.size());

        REQUIRE_THROWS_AS(db.insert_entry(name, name.size(), address, address.size(), phone, phone.size()), std::runtime_error);
    }

    SECTION("select_entries() with non-existent entry") {
        const std::string db_file = "/tmp/test_db_5"
        Database db(db_file);

        std::vector<Entry*> entries = db.select_entries(name, address, phone);

        REQUIRE(entries.empty());
    }

    SECTION("select_entries() with existent entry") {
        const std::string db_file = "/tmp/test_db_6"
        Database db(db_file);
        db.insert_entry(name, name.size(), address, address.size(), phone, phone.size());

        std::vector<Entry*> entries = db.select_entries(name, address, phone);

        REQUIRE_FALSE(entries.empty());
        Entry* matching_entry = entries.at(0);
        REQUIRE(*matching_entry == entry);

        delete entries[0];
    }

    SECTION("select_entries() with wildcards") {
        const std::string db_file = "/tmp/test_db_7"
        Database db(db_file);
        const std::string name_2 = "Juan Perez";
        const std::string address_2 = "Balcarce 950";
        const std::string phone_2 = "0800-4444";
        Entry entry_2(name_2, address_2, phone_2);
        db.insert_entry(name, name.size(), address, address.size(), phone, phone.size());
        db.insert_entry(name_2, name_2.size(), address_2, address_2.size(), phone_2, phone_2.size());

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
