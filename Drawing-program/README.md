# Drawing program

## Dependencies
1. Requires Git, CMake, and OpenGL
1. Fetch submodules ```git submodule update --init --recursive .```

## Instructions

#### Linux

```sh
git clone https://github.com/sindre0830/Drawing-Recognition
mkdir Drawing-Recognition/Drawing-program/Build
cd Drawing-Recognition/Drawing-program/Build
cmake -G "Unix Makefiles" ..
cmake --build .
# run binary
bin/drawing-program
```

#### Windows

```sh
git clone https://github.com/sindre0830/Drawing-Recognition
mkdir Drawing-Recognition/Drawing-program/Build
cd Drawing-Recognition/Drawing-program/Build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build .
# run in Visual Studio
```

#### MacOS (Darwin)
***not tested***

```sh
git clone https://github.com/sindre0830/Drawing-Recognition
mkdir Drawing-Recognition/Drawing-program/Build
cd Drawing-Recognition/Drawing-program/Build
cmake -G "XCode" ..
cmake --build .
# run binary
bin/drawing-program
```
