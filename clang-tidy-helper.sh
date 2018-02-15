#!/bin/bash

rm -rf ct-build
mkdir ct-build
cd ct-build

cmake -DBUILD_TESTS=OFF -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_CLANG_TIDY:STRING="clang-tidy;-checks=*,-google-readability-braces-around-statements,-readability-braces-around-statements,-readability-implicit-bool-cast" ..
# cmake -DBUILD_TESTS=OFF -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_CLANG_TIDY:STRING="clang-tidy;-fix;-checks=*,-google-readability-braces-around-statements,-readability-braces-around-statements,-readability-implicit-bool-cast" ..

make
