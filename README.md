
<!-- PROJECT SHIELDS -->

[![release-branch-status][build-shield]][build-url]
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/Bertouz/CppTemplate/">
    <img src="doc/images/logo.jpg" alt="Logo" width="160" height="160">
  </a>

  <h3 align="center">SignalProcessingPipeline (SPP)</h3>

  <p align="center">
   A small project for building signal processing pipelines in c++
    <br />
    <a href="https://github.com/Bertouz/SignalProcessingPipeline"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Bertouz/SignalProcessingPipeline">View Demo</a>
    ·
    <a href="https://github.com/Bertouz/SignalProcessingPipeline/issues">Report Bug</a>
    ·
    <a href="https://github.com/Bertouz/SignalProcessingPipeline/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

- [Table of Contents](#table-of-contents)
- [About The Project](#about-the-project)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
    - [1. Install CMake](#1-install-cmake)
    - [2. Install Clang tools (optional)](#2-install-clang-tools-optional)
      - [Windows](#windows)
      - [Ubuntu](#ubuntu)
    - [3. Install Doxygen (optional)](#3-install-doxygen-optional)
      - [Windows](#windows-1)
      - [Ubuntu](#ubuntu-1)
    - [4. Install Catch2 (optional)](#4-install-catch2-optional)
      - [Ubuntu](#ubuntu-2)
    - [4. Install gcovr (optional)](#4-install-gcovr-optional)
      - [Ubuntu](#ubuntu-3)
  - [Installation](#installation)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)



## About The Project

Signal Processing Pipeline (SPP) is a simple project that started as an interview exercice but ended in a project for building 1d signal processing pipelines.  

Aims :  
+ Provide primitive for building powerfull processing algorithms
+ Provide primitives for building streaming processing in blocs
+ Provide primitives for building microservices

### Built With
This project is built using CMake.
* [CMake 3.20.4](https://cmake.org)


## Getting Started

In this sections we will explain how to build the project from sources  

### Prerequisites

#### 1. Install CMake 
This project use CMake for build configuration, you will need it.  
Check [CMake](https://cmake.org/download/) official site for more informations.  

#### 2. Install Clang tools (optional)

To do source formatting and static analysis we use clang tools.

##### Windows
Download binaries from [llvm](https://releases.llvm.org/)
Say yes to add Llvm/bin install directory to Path variable when asked

##### Ubuntu
```sh
sudo apt-get install clang-format 
sudo apt-get install clang-tidy
```

To use clang tools it is better to generate compilation database. cmake offer an easy way

```sh
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
ln -s compile_commands.json ../compile_commands.json
```

#### 3. Install Doxygen (optional)

For documation generation we use doxygen.

##### Windows
Download binaries from [Doxygen](https://www.doxygen.nl/download.html)

##### Ubuntu
```sh
sudo apt-get install doxygen
```

#### 4. Install Catch2 (optional)
For unit testing we use [Catch2](https://github.com/catchorg/Catch2)

##### Ubuntu
```sh
cd somewhere_i_want_to_put_catch2_sources
git clone https://github.com/catchorg/Catch2
cd Catch2
mkdir build
cd build
cmake ..
make install
```
#### 4. Install gcovr (optional)

For code coverage reporting I use gcovr 

##### Ubuntu
```sh
sudo apt-get install gcovr
```

### Installation

Now that you have installed the dependencies you need you just have to compile and install the project

1. Clone the repo
```sh
git clone https://github.com/Bertouz/SignalProcessingPipeline
```
2. Build project
```sh
cd CppProject
mkdir build && cd build
cmake -DBUILD_DOC=OFF -DBUILD_TESTS=OFF -DENABLE_CLANG_FORMAT=OFF -DENABLE_CLANG_TIDY=OFF -DENABLE_CODE_COVERAGE=OFF -DCMAKE_INSTALL_PREFIX=path_to_installation_dir ..
make -j4
```

4. Install project
```sh
make install
```

## Roadmap

See the [open issues](https://github.com/Bertouz/SignalProcessingPipeline/issues) for a list of proposed features (and known issues).

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Format the sources with clang-format
5. Run clang-tidy analysis and check for errors
6. Check that the added source code is 100% covered by unit tests
7. Push to the Branch (`git push origin feature/AmazingFeature`)
8. Open a Pull Request
9. Wait for review 



<!-- LICENSE -->
## License

 Distributed under the GNU LESSER GENERAL PUBLIC LICENSE. See `LICENSE` for more information.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Bertouz/SignalProcessingPipeline
[contributors-url]: https://github.com/Bertouz/SignalProcessingPipeline/graphs/contributors
[forks-shield]:  https://img.shields.io/github/forks/Bertouz/SignalProcessingPipeline
[forks-url]: https://github.com/Bertouz/SignalProcessingPipeline/network/members
[issues-shield]: https://img.shields.io/github/issues-raw/Bertouz/SignalProcessingPipeline 
[issues-url]: https://github.com/Bertouz/SignalProcessingPipeline/issues
[license-shield]: https://img.shields.io/github/license/Bertouz/SignalProcessingPipeline
[license-url]: https://github.com/Bertouz/SignalProcessingPipeline/blob/release/LICENSE 
[product-screenshot]: images/doc/images/Logo_template.png
[build-shield]: https://img.shields.io/github/workflow/status/Bertouz/SignalProcessingPipeline/Build/release
[build-url]: https://github.com/Bertouz/SignalProcessingPipeline/workflows/Build
