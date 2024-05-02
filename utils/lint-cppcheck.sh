#!/usr/bin/env bash

set -o xtrace

SOURCES=$(find src -not -path "src/vcpkg**" -not -path "src/build**" -iname "*.cpp" | tr '\n' ' ')
INCLUDES=$(find src -type d -not -path "src/vcpkg**" -not -path "src/build**" -path "**/include" | sed -e "s/.*/-I &/" | tr '\n' ' ')

cppcheck --enable=all --suppressions-list=src/.suppressions.txt  --error-exitcode=1 --check-config $SOURCES $INCLUDES