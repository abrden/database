#include <iostream>
#include "Server.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! I'm the server" << std::endl;

//    Server s(std::stoi(argv[1]), 0, argv[2]);
    Server s("/bin/bash", 'A', argv[2]); // FIXME
    s.run();

    return 0;
}
