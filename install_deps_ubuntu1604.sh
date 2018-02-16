#!/bin/bash

# Update and upgrade first
sudo apt-get update
# sudo apt-get -y upgrade

# Basic things
sudo apt-get -y install build-essential cmake git software-properties-common python-software-properties libboost-dev libgtest-dev wget clang

# Set up gtest
# cd /usr/src/gtest/
# sudo cmake .
# sudo make
# sudo cp *.a /usr/lib

# Prepare to install SFML
sudo apt-get -y install libxrandr-dev libopenal-dev libfreetype6 libfreetype6-dev libflac-dev libogg-dev libvorbis-dev libopenal-dev libudev-dev libsndfile-dev libjpeg-dev libglew-dev

export CC=clang
export CXX=clang++

cd ~
wget https://www.sfml-dev.org/files/SFML-2.4.2-sources.zip
unzip SFML-2.4.2-sources.zip
cd SFML-2.4.2
mkdir build
cd build
cmake .. -DBUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
