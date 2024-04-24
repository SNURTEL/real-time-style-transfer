#!/usr/bin/env bash

set -o xtrace

cppcheck --enable=all --suppressions-list=src/.suppressions.txt  --error-exitcode=1 $(find src -not -path "src/vcpkg**" -not -path "src/build**" \( -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp" \) )