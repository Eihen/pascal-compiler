cmake_minimum_required(VERSION 3.7)
project(pascal_compiler)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Debug)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB SOURCE_FILES
        src/*.h
        src/*.cpp
        src/entry/*.h
        src/entry/*.cpp
        src/type/*.h
        src/type/*.cpp
)

add_executable(pascal_compiler ${SOURCE_FILES})

target_link_libraries(pascal_compiler Threads::Threads)