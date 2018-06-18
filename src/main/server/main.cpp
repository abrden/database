#include <iostream>
#include "Server.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the server" << std::endl;

    Server s(std::string(argv[1]), argv[2][0], std::string(argv[3]));
    s.run();

    return 0;
}
