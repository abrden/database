#include <iostream>

#include "Client.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the client" << std::endl;

    Client c(std::string(argv[1]), argv[2][0]);
    c.run();

    return 0;
}
