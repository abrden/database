#!/bin/bash

echo "==================== Creating build directory ===================="
rm -rf build
mkdir build && cd build
echo "==================== Done ===================="

echo "==================== Compiling project ===================="
cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j4