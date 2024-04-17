cmake_minimum_required(VERSION 3.8)
project(base VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsqlite3") #вызывать при сборке

include(FetchContent)
FetchContent_Declare(sqlite3 URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip)
FetchContent_MakeAvailable(sqlite3)

add_executable(base main.cpp database.h database.cpp)
target_link_libraries(base PRIVATE sqlite3)
