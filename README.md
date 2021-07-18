<!--
*** Thanks for checking out this README Template. If you have a suggestion that would
*** make this better, please fork the repo and create a pull request or simply open
*** an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->


<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

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

  <h3 align="center">Cpp-Template</h3>

  <p align="center">
    A simple and easy template for you C++ projects
    <br />
    <a href="https://github.com/Bertouz/CppTemplate"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Bertouz/CppTemplate">View Demo</a>
    ·
    <a href="https://github.com/Bertouz/CppTemplate/issues">Report Bug</a>
    ·
    <a href="https://github.com/Bertouz/CppTemplate/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

I needed a template for my c++ projects to be more DRY. There is many other C++ template but I needed one that is more specific to me needs:

This template configure a project with unit testing using Catch2, integrate static analysis to the build process with clang-tidy, allow project formatting with clang-format and generate the documentaton with doxygen.

Here's why:
* Documentation generation with doxygen included to the compilation process 
* Static analysis with clang-tidy included to the compilation process
* Code formatting enabled with clang-format
* Code coverage analysis and reporting setup with gcov/lcov/gcovr
* Unit testing setup 

Of course, no one template will serve all projects since your needs may be different. You may also suggest changes by forking this repo and creating a pull request or opening an issue.

A list of commonly used resources that I find helpful are listed in the acknowledgements.

### Built With
This project is built using CMake.
* [CMake 3.14](https://cmake.org)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

#### 1. Install CMake 
This project use CMake for build configuration, you will need it.

##### Windows
Download binaries from [CMake](https://cmake.org/download/)

##### Ubuntu
```sh
sudo apt-get install cmake
```

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
git clone https://github.com/Bertouz/CppProject
```
2. Build project
```sh
cd CppProject
mkdir build && cd build
cmake -DBUILD_DOC=ON -DBUILD_TESTS=OFF -DENABLE_CLANG_FORMAT=OFF -DENABLE_CLANG_TIDY=OFF -DENABLE_CODE_COVERAGE=OFF -DCMAKE_INSTALL_PREFIX=path_to_installation_dir ..
make -j4
```

4. Install project
```sh
make install
```




<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_




<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/Bertouz/CppTemplate/issues) for a list of proposed features (and known issues).

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

 Distributed under the GNU LESSER GENERAL PUBLIC LICENSE. See `LICENSE` for more information.

<!-- CONTACT 
## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

 Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)
-->


<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template)<!-- awsome readme-->
* [Code coverage module](https://github.com/bilke/cmake-modules)<!-- Code coverage module-->





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Bertouz/CppTemplate
[contributors-url]: https://github.com/Bertouz/CppTemplate/graphs/contributors
[forks-shield]:  https://img.shields.io/github/forks/Bertouz/CppTemplate
[forks-url]: https://github.com/Bertouz/CppTemplate/network/members
[issues-shield]: https://img.shields.io/github/issues-raw/Bertouz/CppTemplate 
[issues-url]: https://github.com/Bertouz/CppTemplate/issues
[license-shield]: https://img.shields.io/github/license/Bertouz/CppTemplate
[license-url]: https://github.com/Bertouz/CppTemplate/blob/release/LICENSE 
[product-screenshot]: images/doc/images/Logo_template.png
[build-shield]: https://img.shields.io/github/workflow/status/Bertouz/CppTemplate/Build/release
[build-url]: https://github.com/Bertouz/CppTemplate/workflows/Build
