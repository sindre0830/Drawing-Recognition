# Drawing program

Works on Linux, issues on Windows because of ZeroMQ.

## Instructions

```sh
# Install dependencies
sudo apt-get install gcc g++ cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev mesa-common-dev libzmq3-dev python3-pip
pip3 install pyzmq opencv-python scikit-image tensorflow keras numpy
# Fetch submodules
git submodule update --init --recursive .
# Compile program
mkdir Build
cd Build
cmake ..
cmake --build .
# Run binary
bin/drawing-program
```
