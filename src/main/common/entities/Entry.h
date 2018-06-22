#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <string>

enum ENTRY_BUFF_SIZE {
    NAME = 62,
    ADDRESS = 121,
    PHONE = 14
};

typedef struct {
    char name[ENTRY_BUFF_SIZE::NAME];
    char address[ENTRY_BUFF_SIZE::ADDRESS];
    char phone[ENTRY_BUFF_SIZE::PHONE];
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
        bool weak_equals(const Entry& e) const;
        EntryData serialize() const;
        std::string get_name() const;
        std::string get_address() const;
        std::string get_phone() const;
        std::string to_string() const;
};


#endif //DATABASE_ENTRY_H
