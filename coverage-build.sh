#!/bin/bash

rm -rf build-cov
mkdir build-cov
cd build-cov

cmake .. -DBUILD_VISUALIZER=OFF -DCMAKE_BUILD_TYPE=Coverage
make
make coverage
