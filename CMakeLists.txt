cmake_minimum_required(VERSION 3.4)
project(tabusearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
# no -pedantic since c++98 DOES NOT support long long 
add_compile_options(-Werror -Wall -pedantic -Wno-unused)
# add_compile_options(-Ofast)

add_definitions(-DDOG_DEBUG)
add_definitions(-DSTRIP_NOTIFY=20000)
add_definitions(-DSTRIP=10000)
add_definitions(-DPOPULATION=5)
add_definitions(-DSCALE=1)

# for debugging vector, out_of_bound will be caught
# add_definitions(-D_GLIBCXX_DEBUG)

# only for testing GPX
# add_executable(testGPX testGPX.cpp)

add_executable(main main.cpp)


