## Building in Linux

Follow the steps below to get sources and build Linux binaries in Ubuntu 20.04.

1. Open new terminal window (press *Ctrl+Alt+T* to open it).

2. Make sure you've got all required development tools: *gcc*, *cmake* and *git*. If not, you may easily download them and install:
```sh
sudo apt install gcc cmake git
```

3. Download sources from *github* into your home directory (note: repository contents will be placed in *AoC_cpp* subdirectory):
```sh
cd ~
git clone https://github.com/tbielak/AoC_cpp.git
```

4. Go to the directory containing *CMakeLists.txt*:
```sh
cd AoC_cpp/linux
```

5. Make *build* directory (note: a lot of intermediate files will be placed there, you may remove them after successful build):
```sh
mkdir build
```
6. Enter *build* directory and use *cmake* to generate make files:
```sh
cd build
cmake ..
```
7. Build everything using *make*:
```sh
make
```
Alternatively, to speed up building process - specify number of parallel jobs:
```sh
make -j 8
```

8. Go to *bin* directory - here you'll find the executables:
```sh
cd ../../bin
ls -la
```
9. You can [run](../bin) the executables directly from *bin* directory. Enjoy!