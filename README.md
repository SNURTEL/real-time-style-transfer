# 24L-ZPR

Description goes here.

## Setup

#### Prerequisites
- `CMake`
- CUDA
- _(optional)_ `clang-format`
- _(optional)_ `clang-tidy`
- _(optional)_ `cppcheck`

#### Build

`vcpkg` comes bundled with the project as a git submodule. Install:

```shell
git submodule update --init --update
export VCPKG_ROOT=${PWD}/src/vcpkg
export PATH=$VCPKG_ROOT:$PATH
./src/vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Run `cmake` to configure the build and fetch & build dependencies via `vcpkg`'s manifest mode (this will take a good while!):

```shell
cmake -S src -B build
```

You will most likely get some errors related to missing packages causing dependencies to fail build. Read the logs carefully. Missing packages may include:

```shell
# debian-based distro
libXtst
libxtst-dev
libtool
pkg-config
autoconf-archive
gfortran
cudnn9-cuda-12  # or cudnn9-cuda-11


# RHEL-based distro
libXtst-devel
libtool
pkg-config
autoconf-archive
gfortran
```

If you're getting CUDA-related errors, you may want to try setting `CUDACXX=/path/to/cuda/nvcc` before the first command. This should be something like `CUDACXX=/usr/local/cuda-12.4/bin/nvcc`.

Finally, build the actual package:

```shell
cmake --build build
```

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
