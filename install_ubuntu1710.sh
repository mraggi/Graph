#!/bin/bash

# Update and upgrade first
sudo apt-get update
sudo apt-get -y upgrade


# Remove all traces of previous SFML installation
sudo apt-get remove libsfml-dev
sudo rm -rf /usr/local/share/SFML
sudo rm -rf /usr/local/include/SFML
sudo rm -rf /usr/local/lib/*sfml*
sudo rm -rf /usr/share/SFML
sudo rm -rf /usr/include/SFML
sudo rm -rf /usr/lib/*sfml*

# Basic things
sudo apt-get -y install build-essential mc cmake git software-properties-common python-software-properties libboost-dev libgtest-dev  

# sudo apt-get install libxrandr-dev libopenal-dev libfreetype6 libfreetype6-dev libflac-dev libogg-dev libvorbis-dev libopenal-dev libudev-dev 

# sudo apt-add-repository ppa:sonkun/sfml-stable
# sudo apt-get update
sudo apt-get -y install libsfml-dev

cd /usr/src/gtest/
sudo cmake .
sudo make
sudo cp *.a /usr/lib

cd ~
rm -rf Graph
git clone http://www.github.com/mraggi/Graph
cd Graph
mkdir build
cd build
cmake ..
make
./playground
./graph_tests
./visualizer
