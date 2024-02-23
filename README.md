# 24L-ZPR

Description goes here.

## Setup

#### Prerequisites
- `CMake`
- _(optional)_ `clang-format`
- _(optional)_ `clang-tidy`
- _(optional)_ `cppcheck`

#### Build

```shell
cmake -S src -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
```

The first step may take a few seconds, as CMake needs to pull Catch2 sources.

The `DCMAKE_EXPORT_COMPILE_COMMANDS` is only needed by `clang-tidy`. 

#### Run tests
```shell
ctest --test-dir build
```

## Contributing

Before submitting a PR:

1. Reformat the code

```shell
clang-format -style=file --Werror -i --verbose $(find src -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp")
```

2. Lint with `clang-tidy` and `cppcheck`
```shell
clang-tidy -p build $(find src -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp")
```

```shell
cppcheck --enable=all --suppressions-list=src/.suppressions.txt  --error-exitcode=1 $(find src -iname "*.cpp" -or -iname "*.h" -or -iname "*.hpp")

```

3. Run tests as described above
