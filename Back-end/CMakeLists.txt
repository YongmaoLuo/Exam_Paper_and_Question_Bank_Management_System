cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
option(OPTIMISER "Optimiser level 3" ON)
project(cplusplusproject2022fall CXX)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



include_directories(.)
include_directories(./json/include)
include_directories(./fmt/include)
include_directories(./usr/local/include)
include_directories(./SQLite3-Encryption/src)

include(FetchContent)
FetchContent_Declare(
    glaze
    GIT_REPOSITORY https://github.com/stephenberry/glaze.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glaze)


add_executable(cplusplusproject2022fall
               server_unencrypted.cpp)

target_include_directories(cplusplusproject2022fall PRIVATE include)
target_link_libraries(cplusplusproject2022fall PRIVATE glaze::glaze -lsqlite3 -lssl -lcrypto -fopenmp -fconcepts)