cmake_minimum_required(VERSION 3.19)

project(introduction_to_algorithms VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

function(add_part_executable part_name)
    file(GLOB_RECURSE PART_SOURCES "alg/${part_name}/*.cpp")
    add_executable()
    
endfunction()
