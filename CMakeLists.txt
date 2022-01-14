cmake_minimum_required(VERSION 2.8.3)
project(Test)

add_compile_options(-std=c++11)
add_compile_options(-o2)
add_compile_options(-march=native)
add_compile_options(-lpthread)

include_directories(inc)

set(SRCS 
    src/CanManager.cpp
    src/Math.cpp
    src/M2006.cpp
    src/Pid.cpp
    )

add_executable(Test main.cpp ${SRCS})

target_link_libraries(Test pthread)