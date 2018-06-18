#include <iostream>

#include "FileNames.h"
#include "Server.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the server" << std::endl;

    Server s(MessageQueueInfo::FILE, MessageQueueInfo::LETTER, std::string(argv[1]));
    s.run();

    return 0;
}
