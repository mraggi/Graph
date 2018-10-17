#!/bin/bash

rm -rf build-oclint
mkdir build-oclint
cd build-oclint

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
echo -e "---------------\n"

cd ..
fd "\.cpp" src | xargs xargs -d '\n' oclint -p build-oclint
