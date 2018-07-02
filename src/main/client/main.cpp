#include <iostream>

#include "Client.h"
#include "FileNames.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the client" << std::endl;

    try {
        Client c(MessageQueueInfo::FILE, MessageQueueInfo::LETTER);
        c.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
