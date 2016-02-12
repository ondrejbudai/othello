cmake_minimum_required(VERSION 3.3)
project(othello)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES_CLI GameBoard.cc MainGame.cc Player.cc AI.cc main.cc)
add_executable(othello-cli ${SOURCE_FILES_CLI})
