## Executables

After successful build you'll find your executables here, in *bin* directory. You can run them from this location, as they read puzzle input (by default) from *input* directory.

## Windows executables

[Windows executables](../windows), built in release configuration for x64 platform, will look like this:

File | Description
------------ | -------------
2015_x64_Release.exe | 2015 puzzles solutions
2015_with_CUDA_x64_Release.exe | 2015 puzzles solutions, including solutions running on CUDA device
2019_x64_Release.exe | 2019 puzzles solutions
2020_x64_Release.exe | 2020 puzzles solutions

You can also build them in Debug configuration or for x86 platform. In result you'll see appropriate *exe* files in this folder.

To run executable "as designed", just pick up one and run it from command line prompt, without any parameters:
```sh
> 2020_x64_Release
```

## Linux executables

[Linux executables](../linux), built by *cmake* will look like this:

File | Description
------------ | -------------
2015 | 2015 puzzles solutions (x64 code, O3 optimization)
2019 | 2019 puzzles solutions (x64 code, O3 optimization)
2020 | 2020 puzzles solutions (x64 code, O3 optimization)

To run executable "as designed", just pick up one and run it from bash prompt, without any parameters:
```sh
$ ./2020
```

## Command line options

To get familiar with command line options, run the executable with *-h* switch (help):
```sh
> 2020_x64_Release -h
```

To run single day puzzle solution(s) use *-p* switch and select the day. Example of running 2nd day puzzle solution(s):
```sh
> 2020_x64_Release -p 2
```

Some puzzles have more than one solution of the problem. To see how solutions are available use *-s* switch:
```sh
> 2020_x64_Release -s
```

To run single solution also use *-p* switch and select the day and the solution. Example of running 18th day, 2nd puzzle solution:
```sh
> 2020_x64_Release -p 18:2
```

To run single day solution(s) with your input, place your input file in *bin* directory and put the filename in *-i* switch. Example:
```sh
> 2020_x64_Release -p 2 -i my_2020_02_input.txt
```

To measure execution time of the solution(s) use *-s* switch. In this mode each puzzle solution is run at least file times and at least for five seconds. It may take some time to obtain all results, so please be patient. The highest and the lowest time measurements are dropped, the average time of all remaining executions is printed. Repeatability of results is checked after each execution. These consistency checks and preparing input for subsequent code execution are outside the measurement scope, thus the execution may last longer than expected. Example:
```sh
> 2020_x64_Release -p 2 -s
```

Output printed on console is colored text. Selecting the colors is achieved by emitting escape sequences, which should work fine in Linux out of the box. In Windows this feature in supported by *cmd.exe* and *conhost.exe* starting from Windows 10 TH2 v1511. If you see the garbage instead of colors, use *-c* switch to disable coloring (it is also useful when redirecting output to file for further processing):
```sh
> 2020_x64_Release -p 2 -c
```

## Debugging the solution

Use Microsoft Visual Studio Community 2019 in Windows to debug the solution. Build the executables in Debug configuration, and choose the puzzle solution providing *Command Arguments* (*-p* switch) + optionally: your input file (*-i* switch). Place the breakpoint in the appropriate *cpp* file in *main* routine and run it. Enjoy!
