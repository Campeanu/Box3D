# Box3D
C++ &amp; OpenGL | Box3D engine

# Usage
There are two general ways to use this solution:
1. Build the libraries in the solution and run their unit tests.
2. Build the engine program and its plugins, and configure and run the engine.

# Unit tests
Each library in the solution comes with unit tests. There are two main ways to run the tests:
1. Use [CTest](https://cmake.org/cmake/help/latest/module/CTest.html).
2. Run individual unit test runners directly (e.g. build/Box3D/test/Debug/Box3DTests.exe).

# Programs and libraries hosted in this solution
* 
*
*
# Supported platforms / recommended toolchains
The following are recommended toolchains for popular platforms.
* Windows -- [Visual Studio](https://www.visualstudio.com/) (Microsoft Visual C++)
* Linux -- clang or gcc
* MacOS -- Xcode (clang)

# Building
There are two distinct steps in the build process:
1. Generation of the build system, using CMake   
2. Compiling, linking, etc., using CMake-compatible toolchain

# Prerequisites
* [CMake](https://cmake.org/) version 3.8 or newer
* C++11 toolchain compatible with CMake for your development platform (e.g. [Visual Studio](https://www.visualstudio.com/) on Windows)
# Build system generation 
```bash
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A "x64" ..
```

# Compiling, linking ...
Either use [CMake](https://cmake.org/) or your toolchain's IDE to build.
For [CMake](https://cmake.org/):

```bash
cd build
cmake --build . --config Debug
```