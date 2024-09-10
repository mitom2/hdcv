
# HanDyConVerter: Header-Only C++ Library for Base Conversion
hdcv is a lightweight, single-header C++ library designed for converting numbers between various bases, such as decimal, hexadecimal, and binary. It includes simple functions to check if strings contain numbers or letters, and to convert strings or numbers between various formats and cases.


## Features

- Base conversion of integers (up to base 36).
- Conversion of text and characters between uppercase and lowercase.
- Helper functions for checking if a string or character is numeric or alphabetical.
- Optional command-line utility for converting numbers between bases.
## Run Locally

To get a copy of this project and compile it locally, follow these steps:

```bash
  git clone https://github.com/mitom2/hdcv.git
  cd hdcv
  mkdir build
  cd build
  cmake ..
  make
```
Alternatively, if you don't need the optional command line tool, you can just copy the include/hdcv.hpp header file and use its functions in your project.
## Command line utility usage & example
After building, the executable hdcv will be generated. You can run it as follows:

```bash
./hdcv [number] [source base] [target base] [OPTION]...
```
For example, to convert the binary number 1010 to hexadecimal:

```bash
./hdcv 1010 2 16
```
Command-Line Options:
- -u    Forces uppercase for results in bases > 10.
- -h    Displays help information.

Example:
```bash
./hdcv 255 10 16 -u
```
This will convert the decimal number 255 to uppercase hexadecimal (FF).
## Library usage & example
To use all available functions, you simply need to include the hdcv.hpp file in your project. All functions are in the hdcv namespace. Check [documentation](https://mitom2.github.io/hdcv/) to see functions definitions.

Example program:
```c++
#include "hdcv.hpp"
#include <iostream>

int main() {
    std::string binary = "1010";
    std::string hex = hdcv::toString(hdcv::fromString(binary, 2), 16);
    std::cout << "Binary " << binary << " in hexadecimal: " << hex << std::endl;
}
```
## License
This project is licensed under the terms of the MIT license. Check the LICENSE file for details.

