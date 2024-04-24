#!/usr/bin/env bash

set -o xtrace

clang-format -style=file --Werror -n --verbose $(find src -not -path "src/vcpkg**" -not -path "src/build**" \( -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp" \) )