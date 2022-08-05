# AoC_cpp
[Advent of Code](http://adventofcode.com) solutions in C++ 11/14/17 (Windows x86/x64, Windows with CUDA x64, Linux x64)

## Features
- Advent of Code 2015-2021 solutions in C++ 11/14/17
- using STL only (in non-CUDA solutions)
- ready to build for Windows x86/x64 in Microsoft Visual Studio Community 2019
- ready to build for Windows x64 with CUDA 11.5 to speed up some solutions on various CUDA architectures
- ready to build for Linux x64 (tested with Ubuntu 20.04)

## Puzzle solutions available
- [2021](https://adventofcode.com/2021): ALL + bonus: two different solutions of day 18
- [2020](https://adventofcode.com/2020): ALL + bonus: two different solutions of day 18
- [2019](https://adventofcode.com/2019): days 1-20
- [2018](https://adventofcode.com/2018): days 1-11
- [2017](https://adventofcode.com/2017): days 1-21
- [2016](https://adventofcode.com/2016): days 1-21 + bonus: two different solutions of day 19
- [2015](https://adventofcode.com/2015): ALL + bonuses: one additional multithreaded solution (day 4) + two CUDA solutions (days 4 and 24)

Current status: 296 AoC stars covered (out of 350★)

## Solutions matrix
Year | 2015 | 2016 | 2017 | 2018 | 2019 | 2020 | 2021
 ---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
Day 1|[`S`](sources/2015/2015_01.cpp)| | | | | |
Day 2|[`S`](sources/2015/2015_02.cpp)| | | | | |
Day 3|[`S`](sources/2015/2015_03.cpp)| | | | | |
Day 4|[`S`](sources/2015/2015_04.cpp)| | | | | |
Day 5|[`S`](sources/2015/2015_05.cpp)| | | | | |
Day 6|[`S`](sources/2015/2015_06.cpp)| | | | | |
Day 7|[`S`](sources/2015/2015_07.cpp)| | | | | |
Day 8|[`S`](sources/2015/2015_08.cpp)| | | | | |
Day 9|[`S`](sources/2015/2015_09.cpp)| | | | | |
Day 10|[`S`](sources/2015/2015_10.cpp)| | | | | |
Day 11|[`S`](sources/2015/2015_11.cpp)| | | | | |
Day 12|[`S`](sources/2015/2015_12.cpp)| | | | | |
Day 13|[`S`](sources/2015/2015_13.cpp)| | | | | |
Day 14|[`S`](sources/2015/2015_14.cpp)| | | | | |
Day 15|[`S`](sources/2015/2015_15.cpp)| | | | | |
Day 16|[`S`](sources/2015/2015_16.cpp)| | | | | |
Day 17|[`S`](sources/2015/2015_17.cpp)| | | | | |
Day 18|[`S`](sources/2015/2015_18.cpp)| | | | | |
Day 19|[`S`](sources/2015/2015_19.cpp)| | | | | |
Day 20|[`S`](sources/2015/2015_20.cpp)| | | | | |
Day 21|[`S`](sources/2015/2015_21.cpp)| | | | | |
Day 22|[`S`](sources/2015/2015_22.cpp)| | | | | |
Day 23|[`S`](sources/2015/2015_23.cpp)| | | | | |
Day 24|[`S`](sources/2015/2015_24.cpp)| | | | | |
Day 25|[`S`](sources/2015/2015_25.cpp)| | | | | |

## Repository contents
Repository contains the following directories:

Directory | Contents
------------ | -------------
[bin/input](bin/input) | My input of all puzzles.
[bin](bin) | Initially empty, but here you'll find executables after successful build. You can run them from this location, as they read puzzle input from *input* directory by default. Look inside to learn how to run the solutions from command line/bash prompt.
[linux](linux) | Contains *CMakeLists.txt* used to build executables in Linux, using *gcc* and *cmake*. Look inside and follow step-by-step recipe to build the code in Ubuntu 20.04.
[sources](sources) | Source files. Review and enjoy.
[windows](windows) | Microsoft Visual Studio Community 2019 solutions and projects configured to easily build executables for Windows. Look inside to learn how to build and debug the code in Windows.
