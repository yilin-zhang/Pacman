# Pacman

This is a Pacman game based on OpenGL and OpenMP.

![screenshot](./img/screenshot.png)

## Build

The game is developed on macOS Mojave 10.14.6. It also gets tested on Arch
Linux.

On macOS, make sure you have `cmake` `llvm` and `libomp` installed. If not, make sure
you have Homebrew installed and follow the command below:

```sh
brew install cmake llvm libomp
```

The `CMakeLists.txt` in `src/` is for both macOS Mojave and Arch Linux. To build
the program, make sure you are in the project directory, then follow the
commands below:

```sh
mkdir build
cd build/
cmake ../src
make
./Pacman
```

Then the program should run.
