#!/bin/bash
sudo pacman -S --needed sfml git cmake boost gtest clang gcc kdevelop mc aria2 mlocate fish
rm -rf Graph
git clone https://github.com/mraggi/Graph
cd Graph
mkdir build
cd build
cmake ..
make
