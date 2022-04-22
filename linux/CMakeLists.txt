cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

# 2015 Solutions
project(2015)
file(GLOB src2015 "../sources/2015/*.cpp" "../sources/shared/*.cpp")
list(FILTER src2015 EXCLUDE REGEX ".*_cuda.cpp$")
list(FILTER src2015 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2015 ${src2015})
target_link_libraries(2015 pthread)

# 2016 Solutions
project(2016)
file(GLOB src2016 "../sources/2016/*.cpp" "../sources/shared/*.cpp" "../sources/MD5/*.cpp")
list(FILTER src2016 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2016 ${src2016})
target_link_libraries(2016 pthread)

# 2017 Solutions
project(2017)
file(GLOB src2017 "../sources/2017/*.cpp" "../sources/shared/*.cpp")
list(FILTER src2017 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2017 ${src2017})

# 2018 Solutions
project(2018)
file(GLOB src2018 "../sources/2018/*.cpp" "../sources/shared/*.cpp")
list(FILTER src2018 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2018 ${src2018})

# 2019 Solutions
project(2019)
file(GLOB src2019 "../sources/2019/*.cpp" "../sources/shared/*.cpp")
list(FILTER src2019 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2019 ${src2019})

# 2020 Solutions
project(2020)
file(GLOB src2020 "../sources/2020/*.cpp" "../sources/shared/*.cpp")
list(FILTER src2020 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2020 ${src2020})

# 2021 Solutions
project(2021)
file(GLOB src2021 "../sources/2021/*.cpp" "../sources/shared/*.cpp")
list(FILTER src2021 EXCLUDE REGEX ".*CUDA_misc.cpp$")
add_executable(2021 ${src2021})
