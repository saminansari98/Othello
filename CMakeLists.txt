cmake_minimum_required(VERSION 3.9)
project(Othello)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH /Users/samin/Qt/5.8/clang_64/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Network)
find_package(Qt5Widgets)


set(SOURCE_FILES main.cpp Client.cpp Client.h Constants.h GameController.cpp GameController.h)
add_executable(Othello ${SOURCE_FILES})


target_link_libraries(Othello Qt5::Network)
target_link_libraries(Othello Qt5::Widgets)