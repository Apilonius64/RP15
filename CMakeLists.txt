cmake_minimum_required(VERSION 3.0)
project(rp15)

file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE data res/*)

add_executable(rp15 ${sources} ${data})
target_include_directories(rp15 PUBLIC src/)

file(COPY ${data} DESTINATION res)