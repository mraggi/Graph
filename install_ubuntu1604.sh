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
sudo apt-get -y install build-essential mc cmake git software-properties-common python-software-properties libboost-dev libgtest-dev wget aria2 clang

# Set up gtest
cd /usr/src/gtest/
sudo cmake .
sudo make
sudo cp *.a /usr/lib

# Prepare to install SFML
sudo apt-get -y install libxrandr-dev libopenal-dev libfreetype6 libfreetype6-dev libflac-dev libogg-dev libvorbis-dev libopenal-dev libudev-dev libsndfile-dev libjpeg-dev libglew-dev

export CC=clang
export CXX=clang++

cd ~
aria2c https://www.sfml-dev.org/files/SFML-2.4.2-sources.zip
unzip SFML-2.4.2-sources.zip
cd SFML-2.4.2
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install

cd ~
rm -rf Graph
git clone http://www.github.com/mraggi/Graph
cd Graph
mkdir build
cd build
cmake ..
make
