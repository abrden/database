#include <iostream>

#include "FileNames.h"
#include "Server.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the server" << std::endl;

    Server s(MessageQueueInfo::FILE, MessageQueueInfo::LETTER, DatabaseInfo::DB_FILE);
    s.run();

    return 0;
}
