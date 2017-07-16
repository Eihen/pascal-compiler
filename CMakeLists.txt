cmake_minimum_required(VERSION 3.7)
project(pascal_compiler)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/Debug)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES
        src/Helper.cpp
        src/Helper.h
        src/LexicalAnalyzer.cpp
        src/LexicalAnalyzer.h
        src/main.cpp
        src/Parser.cpp
        src/Parser.h
        src/TableRow.cpp
        src/TableRow.h
        src/Token.cpp
        src/Token.h
        src/TokenQueue.cpp
        src/TokenQueue.h)

add_executable(pascal_compiler ${SOURCE_FILES})

target_link_libraries(pascal_compiler Threads::Threads)