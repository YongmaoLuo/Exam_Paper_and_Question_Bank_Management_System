cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
option(OPTIMISER "Optimiser level 3" ON)
project(cplusplusproject2022fall CXX)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



include_directories(.)
include_directories(./json/include)
include_directories(./fmt/include)
include_directories(./usr/local/include)
include_directories(./sqlite)


add_executable(cplusplusproject2022fall
        server_unencrypted.cpp)

target_link_libraries(cplusplusproject2022fall -lsqlite3)