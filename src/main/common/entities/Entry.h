#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>
#include <ostream>

enum ENTRY_BUFF_SIZE {
    NAME = 62,
    ADDRESS = 121,
    PHONE = 14
};

typedef struct {
    char name[ENTRY_BUFF_SIZE::NAME];
    size_t name_size;
    char address[ENTRY_BUFF_SIZE::ADDRESS];
    size_t address_size;
    char phone[ENTRY_BUFF_SIZE::PHONE];
    size_t phone_size;
} EntryData;

class Entry {
    private:
        std::string name;
        std::string address;
        std::string phone;
    public:
        Entry(const std::string& name, const std::string& address, const std::string& phone);
        Entry(std::string& entry_str);
        bool operator ==(const Entry& e) const;
        friend std::ostream &operator<<(std::ostream &os, const Entry &entry);
        bool matches(const Entry &e) const;
        EntryData serialize() const;
        std::string get_name() const;
        std::string get_address() const;
        std::string get_phone() const;
        std::string to_string() const;
};


#endif //DATABASE_ENTRY_H
