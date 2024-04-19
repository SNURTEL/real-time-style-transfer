# 24L-ZPR

Description goes here.

## Setup

#### Prerequisites
- `cmake`
- CUDA
- OpenCV
- Libtorch
- _(optional)_ `clang-format`
- _(optional)_ `clang-tidy`
- _(optional)_ `cppcheck`

#### Build

Assuming you have installed all dependencies, run `cmake` to configure the build (this will take a second, since cmake will need to fetch the Catch2 library):

```shell
cmake -S src -B build
```

If your cmake struggles to find CUDA, Libtorch or OpenCV, you can specify their location by setting the respective env variable:
- CUDA - `CUDACXX=/path/to/cuda/nvcc` (usually something like `CUDACXX=/usr/local/cuda-12.4/bin/nvcc`)
- Libtorch - `Torch_DIR`
- OpenCV - `OpenCV_DIR`


Finally, build the actual package:

```shell
cmake --build build
```

#### Run tests
```shell
ctest --test-dir build
```


#### Alternative: using `vcpkg`
- If you have plenty of time and CPU horsepower and you *really* don't want to clutter up your system with extra libraries, you can try using `vcpkg` to pull and build dependencies from source (this is not recommended and has a good chance of failing). Init `vcpkg` as submodule:


```shell
git submodule update --init --update
export VCPKG_ROOT=${PWD}/src/vcpkg
export PATH=$VCPKG_ROOT:$PATH
./src/vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Add a `USE_VCPKG` flag to cmake. Dependencies will be fetched while configuring the project

```shell
cmake -S src -B build -DUSE_VCPKG
```

Those libraries may come in handy:

```shell
# debian-based
sudo apt install libXtst libxtst-dev libtool pkg-config autoconf-archive gfortran cudnn9-cuda-12  # or cudnn9-cuda-11

# RHEL-based 
sudo dnf install libXtst-devel libtool pkg-config autoconf-archive gfortran cudnn9-cuda-12  # or cudnn9-cuda-11
```

#### Windows
1. Download Cuda Toolkit and add path to kit to Path variable
2. Download Torch and add path to Path variable
3. Download OpenCV and add path to Path variable
   - set `OpenCV_DIR` variable with value of downloaded library path
4. Install QT 6.7.0 with MSVC toolchain to directory `C:/QT`
   - set `QT_QPA_PLATFORM_PLUGIN_PATH` variable to path to `C:/Qt/6.7.0/<msvc qt toolchain version>/plugins/platforms`

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
