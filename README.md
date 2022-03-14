# AoC_cpp
[Advent of Code](http://adventofcode.com) solutions in C++ 11/14/17 (Windows x86/x64, Windows with CUDA x64, Linux x64)

## Features
- Advent of Code 2015-2021 solutions in C++ 11/14/17
- using STL only (in non-CUDA solutions)
- ready to build for Windows x86/x64 in Microsoft Visual Studio Community 2019
- ready to build for Windows x64 with CUDA 11.5 to speed up some solutions on various CUDA architectures
- ready to build for Linux x64 (tested with Ubuntu 20.04)

## Puzzle solutions available
- [2021](https://adventofcode.com/2021): days 1-23 and day 25 + bonus: two different solutions of day 18
- [2020](https://adventofcode.com/2020): ALL + bonus: two different solutions of day 18
- [2019](https://adventofcode.com/2019): days 1-20
- [2018](https://adventofcode.com/2018): none
- [2017](https://adventofcode.com/2017): days 1-10
- [2016](https://adventofcode.com/2016): days 1-18
- [2015](https://adventofcode.com/2015): ALL + bonuses: one additional multithreaded solution (day 4) + two CUDA solutions (days 4 and 24)

## Repository contents
Repository contains the following directories:

Directory | Contents
------------ | -------------
[bin/input](bin/input) | My input of all puzzles.
[bin](bin) | Initially empty, but here you'll find executables after successful build. You can run them from this location, as they read puzzle input from *input* directory by default. Look inside to learn how to run the solutions from command line/bash prompt.
[linux](linux) | Contains *CMakeLists.txt* used to build executables in Linux, using *gcc* and *cmake*. Look inside and follow step-by-step recipe to build the code in Ubuntu 20.04.
[sources](sources) | Source files. Review and enjoy.
[windows](windows) | Microsoft Visual Studio Community 2019 solutions and projects configured to easily build executables for Windows. Look inside to learn how to build and debug the code in Windows.
