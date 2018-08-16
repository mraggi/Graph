#!/bin/bash

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
PACKAGES='mc cmake git gtest-devel boost-devel gcc gcc-c++'
sudo dnf -y install $PACKAGES
rpm --query --queryformat "" $PACKAGES
if [ "$?" -eq 0 ] #if there is a problem installing dependencies the script stops
then
    #Install SFML
    sudo dnf -y install SFML-devel
    PACKAGES='SFML SFML-devel'
    rpm --query --queryformat "" $PACKAGES
    if [ "$?" -eq 0 ]
    then
    cd ~
        rm -rf Graph
        git clone https://github.com/mraggi/Graph
        cd Graph
        mkdir build
        cd build
        cmake ..
        make
    else
        echo "Error installing SFML"
    fi
else
    echo "Error installing dependencies"
fi
