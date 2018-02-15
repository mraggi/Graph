#!/bin/bash

rm -rf cppcheck-build
mkdir cppcheck-build
cd cppcheck-build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
echo -e "---------------\n"

cppcheck --project=compile_commands.json --enable=all > cppcheckoutput.txt
cd ..
