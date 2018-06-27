#include <iostream>

#include "FileNames.h"
#include "Server.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the server" << std::endl;

    try {
        Server s(MessageQueueInfo::FILE, MessageQueueInfo::LETTER, std::string(argv[1]));
        s.run();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
