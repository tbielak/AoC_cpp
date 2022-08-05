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
Day 1|[`.cpp`](sources/2015/2015_01.cpp)[`.h`](sources/2015/2015_01.h)| | | | | |
Day 2|[`.cpp`](sources/2015/2015_02.cpp)[`.h`](sources/2015/2015_02.h)| | | | | |
Day 3|[`.cpp`](sources/2015/2015_03.cpp)[`.h`](sources/2015/2015_03.h)| | | | | |
Day 4|[`.cpp`](sources/2015/2015_04.cpp)[`.h`](sources/2015/2015_04.h)| | | | | |
Day 5|[`.cpp`](sources/2015/2015_05.cpp)[`.h`](sources/2015/2015_05.h)| | | | | |
Day 6|[`.cpp`](sources/2015/2015_06.cpp)[`.h`](sources/2015/2015_06.h)| | | | | |
Day 7|[`.cpp`](sources/2015/2015_07.cpp)[`.h`](sources/2015/2015_07.h)| | | | | |
Day 8|[`.cpp`](sources/2015/2015_08.cpp)[`.h`](sources/2015/2015_08.h)| | | | | |
Day 9|[`.cpp`](sources/2015/2015_09.cpp)[`.h`](sources/2015/2015_09.h)| | | | | |
Day 10|[`.cpp`](sources/2015/2015_10.cpp)[`.h`](sources/2015/2015_10.h)| | | | | |
Day 11|[`.cpp`](sources/2015/2015_11.cpp)[`.h`](sources/2015/2015_11.h)| | | | | |
Day 12|[`.cpp`](sources/2015/2015_12.cpp)[`.h`](sources/2015/2015_12.h)| | | | | |
Day 13|[`.cpp`](sources/2015/2015_13.cpp)[`.h`](sources/2015/2015_13.h)| | | | | |
Day 14|[`.cpp`](sources/2015/2015_14.cpp)[`.h`](sources/2015/2015_14.h)| | | | | |
Day 15|[`.cpp`](sources/2015/2015_15.cpp)[`.h`](sources/2015/2015_15.h)| | | | | |
Day 16|[`.cpp`](sources/2015/2015_16.cpp)[`.h`](sources/2015/2015_16.h)| | | | | |
Day 17|[`.cpp`](sources/2015/2015_17.cpp)[`.h`](sources/2015/2015_17.h)| | | | | |
Day 18|[`.cpp`](sources/2015/2015_18.cpp)[`.h`](sources/2015/2015_18.h)| | | | | |
Day 19|[`.cpp`](sources/2015/2015_19.cpp)[`.h`](sources/2015/2015_19.h)| | | | | |
Day 20|[`.cpp`](sources/2015/2015_20.cpp)[`.h`](sources/2015/2015_20.h)| | | | | |
Day 21|[`.cpp`](sources/2015/2015_21.cpp)[`.h`](sources/2015/2015_21.h)| | | | | |
Day 22|[`.cpp`](sources/2015/2015_22.cpp)[`.h`](sources/2015/2015_22.h)| | | | | |
Day 23|[`.cpp`](sources/2015/2015_23.cpp)[`.h`](sources/2015/2015_23.h)| | | | | |
Day 24|[`.cpp`](sources/2015/2015_24.cpp)[`.h`](sources/2015/2015_24.h)| | | | | |
Day 25|[`.cpp`](sources/2015/2015_25.cpp)[`.h`](sources/2015/2015_25.h)| | | | | |

## Repository contents
Repository contains the following directories:

Directory | Contents
------------ | -------------
[bin/input](bin/input) | My input of all puzzles.
[bin](bin) | Initially empty, but here you'll find executables after successful build. You can run them from this location, as they read puzzle input from *input* directory by default. Look inside to learn how to run the solutions from command line/bash prompt.
[linux](linux) | Contains *CMakeLists.txt* used to build executables in Linux, using *gcc* and *cmake*. Look inside and follow step-by-step recipe to build the code in Ubuntu 20.04.
[sources](sources) | Source files. Review and enjoy.
[windows](windows) | Microsoft Visual Studio Community 2019 solutions and projects configured to easily build executables for Windows. Look inside to learn how to build and debug the code in Windows.
