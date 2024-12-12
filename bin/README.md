## Executables

After successful build you'll find your executables here, in *bin* directory. You can run them from this location, as they read puzzle input (by default) from *input* directory.

## Windows executables

[Windows executables](../windows), built in release configuration for x64 platform, will look like this:

File | Description
------------ | -------------
2015_x64_Release.exe | 2015 puzzles solutions
2015_with_CUDA_x64_Release.exe | 2015 puzzles solutions, including solutions running on CUDA device
2016_x64_Release.exe | 2016 puzzles solutions
2017_x64_Release.exe | 2017 puzzles solutions
2018_x64_Release.exe | 2018 puzzles solutions
2019_x64_Release.exe | 2019 puzzles solutions
2020_x64_Release.exe | 2020 puzzles solutions
2021_x64_Release.exe | 2021 puzzles solutions
2022_x64_Release.exe | 2022 puzzles solutions
2023_x64_Release.exe | 2023 puzzles solutions
2024_x64_Release.exe | 2024 puzzles solutions

You can also build them in Debug configuration or for x86 platform. In result you'll see appropriate *exe* files in this folder.

To run executable "as designed", just pick up one and run it from command line prompt, without any parameters:
```sh
> 2024_x64_Release
```

## Linux executables

[Linux executables](../linux), built by *cmake* will look like this:

File | Description
------------ | -------------
2015 | 2015 puzzles solutions (x64 code, O3 optimization)
2016 | 2016 puzzles solutions (x64 code, O3 optimization)
2017 | 2017 puzzles solutions (x64 code, O3 optimization)
2018 | 2018 puzzles solutions (x64 code, O3 optimization)
2019 | 2019 puzzles solutions (x64 code, O3 optimization)
2020 | 2020 puzzles solutions (x64 code, O3 optimization)
2021 | 2021 puzzles solutions (x64 code, O3 optimization)
2022 | 2022 puzzles solutions (x64 code, O3 optimization)
2023 | 2023 puzzles solutions (x64 code, O3 optimization)
2024 | 2024 puzzles solutions (x64 code, O3 optimization)

To run executable "as designed", just pick up one and run it from bash prompt, without any parameters:
```sh
$ ./2024
```

## Command line options

To get familiar with command line options, run the executable with *-h* switch (help):
```sh
> 2024_x64_Release -h
```

To run single day puzzle solution(s) use *-p* switch and select the day. Example of running 7th day puzzle solution(s):
```sh
> 2021_x64_Release -p 7
```

Some puzzles have more than one solution of the problem. To see how many solutions is available use *-a* switch:
```sh
> 2020_x64_Release -a
```

To run single solution also use *-p* switch and select the day and the solution. Example of running 18th day, 2nd puzzle solution:
```sh
> 2021_x64_Release -p 18:2
```

To run single day solution(s) with your input, place your input file in *bin* directory and put the filename in *-i* switch. Example:
```sh
> 2021_x64_Release -p 2 -i my_2021_02_input.txt
```

To measure execution time of the solution(s) use *-s* switch. In this mode each puzzle solution is run at least ten times and at least for specified seconds (ten seconds, if numeric value is not provided after *-s* switch). It may take some time to obtain all results, so please be patient. 10% of the highest and 10% of the lowest time measurements are dropped, the average time of all remaining executions is printed. Repeatability of results is checked after each execution. These consistency checks and preparing input data for subsequent code executions are outside the measurement scope, thus the execution may last longer than expected. Time of execution does not include input file loading, but includes processing input data (from vector of strings to any other structure needed by solution). Command example:
```sh
> 2021_x64_Release -p 2 -s 15
```

Output is printed on console using colored text. Selecting the colors is achieved by emitting escape sequences, which should work fine in Linux out of the box. In Windows this feature in supported by *cmd.exe* and *conhost.exe* starting from Windows 10 TH2 v1511. If you see garbage instead of colors, use *-c* switch to disable coloring (it is also useful when redirecting output to file for further processing):
```sh
> 2021_x64_Release -p 2 -c
```

## Debugging the solution

Use Microsoft Visual Studio Community 2022 in Windows to debug the solution. Build the executables in Debug configuration, and choose the puzzle solution providing *Command Arguments* (*-p* switch) + optionally: your input file (*-i* switch). Place the breakpoint in the appropriate *cpp* file in *Main::part_one* or *Main::part_two* method and run it. Enjoy!
