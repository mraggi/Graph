!/bin/bash

#Update first
sudo dnf -y update --refresh
sudo dnf -y upgrade

#Remove SFML
sudo dnf -y remove SFML-devel
sudo rm -rf /usr/include/SFML
sudo rm /usr/share/cmake/Modules/FindSFML.cmake
sudo rm -rf /usr/share/doc/SFML-devel
sudo rm -rf /usr/share/doc/SFML
sudo rm -rf /usr/lib64/libsfml-*
sudo rm -rf /usr/lib64/pkgconfig/sfml-*

#Basic things
sudo dnf -y install mc cmake git gtest-devel boost-devel 

#Install SFML
sudo dnf -y install SFML-devel

cd ~
rm -rf Graph
git clone https://github.com/mraggi/Graph
cd Graph
mkdir build
cd build
cmake ..
make
