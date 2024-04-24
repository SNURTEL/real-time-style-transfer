#!/usr/bin/env bash

set -o xtrace

clang-tidy -p build $(find src -not -path "src/vcpkg**" -not -path "src/build**" \( -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp" \) )
