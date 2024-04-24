#!/usr/bin/env bash

set -o xtrace

clang-format -i -style=file --Werror --verbose $(find src -not -path "src/vcpkg**" -not -path "src/build**" \( -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp" \) )