#include <iostream>

#include "Client.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the client" << std::endl;

    Client c(std::stoi(argv[1]));
    c.run();

    return 0;
}
