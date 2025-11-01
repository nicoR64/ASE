# Game of Life Kata - README

This project implements the exercise 3 of exercise sheet 1 in C++ and includes unit tests using **GoogleTest**.

## Prerequisites
- C++ 17 compatible compiler
- CMake Version 3.14 or greater
- working internet connection to fetch GoogleTest with CMake

## Build and Run Instructions

1. First, create a build directory inside the `src/` directory

```
cd src
mkdir build
cd build
```

2. Then, generate the required build files with CMake
```
cmake ..
```

3. After that, compile the kata project

```
cmake --build .
```
This will create a new file called `tests.exe`

4. Finally, run the tests with
```
tests.exe
```
