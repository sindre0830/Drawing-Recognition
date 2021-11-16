# Drawing program

## Dependencies
- Requires Git, CMake, Python 3.9.7 (devel), and OpenGL
    - Python for windows: When running the installer, enable "Download debug binaries". Also needs to add it to PATH
    - Linux: ```sudo dnf install python-devel```
- Fetch submodules ```git submodule update --init --recursive .```

## Instructions

```sh
git clone https://github.com/sindre0830/Drawing-Recognition
mkdir Drawing-Recognition/Drawing-program/Build
cd Drawing-Recognition/Drawing-program/Build
cmake ..
cmake --build .
# run binary
bin/drawing-program
```
