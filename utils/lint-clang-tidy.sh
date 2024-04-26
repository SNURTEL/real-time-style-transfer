#!/usr/bin/env bash

# $1 - cmake preset name

set -o xtrace

clang-tidy -p src/build/$1 -warnings-as-errors=* $(find src -not -path "src/vcpkg**" -not -path "src/build**" \( -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp" \) )
