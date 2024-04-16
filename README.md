# 24L-ZPR

Description goes here.

## Setup

#### Prerequisites
- `CMake`
- _(optional)_ `clang-format`
- _(optional)_ `clang-tidy`
- _(optional)_ `cppcheck`

#### Build

`vcpkg` comes bundled with the project as a git submodule. Install:

```shell
git submodule update --init --update
export VCPKG_ROOT=${PWD}/vcpkg
export PATH=$VCPKG_ROOT:$PATH
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Then, install `vcpkg` dependencies from manifest file (this WILL take a while!):

```shell
vcpkg install | tee -a vcpkg.log
```

You will most likely get some errors related to missing packages causing dependencies to fail build. Read the logs carefully. Missing packages may include:

```shell
# debian-based
libXtst
libxtst-dev
libtool

# RHEL-based
libXtst-devel
libtool
```

Finally, build the actual package:

```shell
cmake -S src -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
```

The `DCMAKE_EXPORT_COMPILE_COMMANDS` is only needed by `clang-tidy`. If you're getting CUDA-related errors, you may want to try setting `CUDACXX=/path/to/cuda/nvcc` before the first command. This should be something like `CUDACXX=/usr/local/cuda-12.4/bin/nvcc`.

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
