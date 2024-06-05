# 24L-ZPR

Description goes here.

[Full documentation](doc/doc.md)

## Setup

#### Prerequisites
- `cmake` (>= 3.25)
- CUDA (12.X)
- OpenCV (4.5.5)
   - Depending on your system, `libfmt-dev` / `fmt-devel` may also be needed
- Libtorch (6.3.1)
- Qt (6.7)
- CPython 3.12
- _(optional)_ `clang-format`
- _(optional)_ `clang-tidy`
- _(optional)_ `cppcheck`

#### Build

Assuming you have installed all dependencies, run `cmake` to configure the build (this will take a second, since cmake will need to fetch the Catch2 library):

```shell
cmake -S src --preset=<PRESET_NAME>
```

For convenience, we will assume you are using the `unix-gcc` preset. Consult `src/CMakePresets.json`.

If your cmake struggles to find CUDA, Libtorch or OpenCV, you can specify their location by setting the respective env variable:
- CUDA - `CUDACXX=/path/to/cuda/nvcc` (usually something like `CUDACXX=/usr/local/cuda-12.4/bin/nvcc`)
- Libtorch - `Torch_DIR`
- OpenCV - `OpenCV_DIR`

If you encounter errors with Qt, prefer setting the path with `cmake` argument `-DCMAKE_PREFIX_PATH=/path/to/qt` rather than with `Qt_DIR` env variable - it may be able to find all library components.

If you want to download models directly from the app, python development headers mus be installed. CMake will look from for version 3.9-3.12 automatically, you can also specify a version explicitly with `-DPYTHON_VERSION=<python3XX>`

Finally, build the actual package:

```shell
cmake --build src/build/unix-gcc
```

#### Run tests
```shell
cd src
ctest --preset test-unix-gcc
```

#### Build documentation

Using `doxygen`

```shell
doxygen Doxyfile
firefox doc/generated/html/index.html
```

#### Alternative: using `vcpkg`
- If you have plenty of time and CPU horsepower and you *really* don't want to clutter up your system with extra libraries, you can try using `vcpkg` to pull and build dependencies from source (this is not recommended and has a good chance of failing). Also note that `vcpkg` port versions may differ slightly from requirements.  Init `vcpkg` as submodule:


```shell
git submodule update --init --update
export VCPKG_ROOT=${PWD}/src/vcpkg
export PATH=$VCPKG_ROOT:$PATH
./src/vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Add a `USE_VCPKG` flag to cmake. Dependencies will be fetched while configuring the project

```shell
cmake -S src --preset=unix-gcc -DUSE_VCPKG
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

## Model
1. Install dependencies for python3
```shell
pip3 install numpy
pip3 install Pillow
pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118
```
2. Run script
```shell
python3 scripts/create-cyclegan-pretrained.py
```

## Contributing

Before submitting a PR:

1. Reformat the code

```shell
./utils/reformat.sh
```

2. Lint with `clang-tidy` and `cppcheck`
```shell
./utils/lint-clang-tidy.sh unix-gcc

./utils/lint-cppcheck.sh
```

3. Run tests as described above
