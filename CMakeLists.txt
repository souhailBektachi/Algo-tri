cmake_minimum_required(VERSION 3.16.3)
project(Algo_tri C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Algo_tri
        lib/funcLib.c
        lib/funcLib.h
        main.c
        lib/sortLib.c
        lib/sortLib.h
        lib/dataLib.c
        lib/dataLib.h
        lib/caseLib.c
        lib/caseLib.h)

find_package(Threads REQUIRED)
target_link_libraries(Algo_tri PRIVATE Threads::Threads)

target_compile_options(Algo_tri PRIVATE -pthread)
set_target_properties(Algo_tri PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})