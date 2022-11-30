# AoC.cpp
[Advent of Code](http://adventofcode.com) solutions in C++ 11/14/17 (Windows x86/x64, Windows with CUDA x64, Linux x64)


## Features
- Advent of Code 2015-2021 solutions in C++ 11/14/17
- using STL only (in non-CUDA solutions)
- ready to build for Windows x86/x64 in Microsoft Visual Studio Community 2022
- ready to build for Windows x64 with CUDA 11.5 to speed up some solutions on various CUDA architectures
- ready to build for Linux x64 (tested with Ubuntu 20.04)


## Solutions matrix
AoC.cpp | 2015 | 2016 | 2017 | 2018 | 2019 | 2020 | 2021 | 2022
------: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--:
Day 1 | [⭐](sources/2015/2015_01.cpp) | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 2 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 3 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 4 | ☀ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 5 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 6 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 7 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 8 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 9 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 10 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 11 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 12 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 13 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 14 | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ | ⭐ |
Day 15 | ⭐ | ⭐ | ⭐ |   | ⭐ | ⭐ | ⭐ |
Day 16 | ⭐ | ⭐ | ⭐ |   | ⭐ | ⭐ | ⭐ |
Day 17 | ⭐ | ⭐ | ⭐ |   | ⭐ | ⭐ | ⭐ |
Day 18 | ⭐ | ⭐ | ⭐ |   | ⭐ | ☀ | ☀ |
Day 19 | ⭐ | ☀ | ⭐ |   | ⭐ | ⭐ | ⭐ |
Day 20 | ⭐ | ⭐ | ⭐ |   | ⭐ | ⭐ | ⭐ |
Day 21 | ⭐ | ⭐ | ⭐ |   |   | ⭐ | ⭐ |
Day 22 | ⭐ |   | 🌟 |   |   | ⭐ | ⭐ |
Day 23 | ⭐ |   | 🌟 |   |   | ⭐ | ⭐ |
Day 24 | ☀ |   | ⭐ |   |   | ⭐ | 🌟 |
Day 25 | ⭐ |   | ⭐ |   |   | ⭐ | ⭐ |

Legend:
⭐ = solution available (both parts)
🌟 = solution available and explained!
☀ = multiple solutions available

Current status: **310** AoC stars covered


## Repository contents
Repository contains the following directories:

Directory | Contents
------------ | -------------
[bin/input](bin/input) | My input of all puzzles.
[bin](bin) | Initially empty, but here you'll find executables after successful build. You can run them from this location, as they read puzzle input from *input* directory by default. Look inside to learn how to run the solutions from command line/bash prompt.
[doc](doc) | Several solutions explained.
[linux](linux) | Contains *CMakeLists.txt* used to build executables in Linux, using *gcc* and *cmake*. Look inside and follow step-by-step recipe to build the code in Ubuntu 20.04.
[sources](sources) | Source files. Review and enjoy.
[windows](windows) | Microsoft Visual Studio Community 2022 solutions and projects configured to easily build executables for Windows. Look inside to learn how to build and debug the code in Windows.
