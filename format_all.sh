#!/bin/bash
find . -iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp | xargs clang-format -i
