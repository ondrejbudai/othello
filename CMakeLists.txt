cmake_minimum_required(VERSION 3.3)
project(othello)

find_package(Qt5Widgets)


##include_directories(${Qt5Widgets_INCLUDES})
#add_definitions(${Qt5Widgets_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

set(SOURCE_FILES_CLI GameBoard.cc MainGame.cc GameLogic.cc Player.cc AI.cc main.cc)
add_executable(othello-cli ${SOURCE_FILES_CLI})
set(SOURCE_FILES_QT main-qt.cc)
add_executable(othello-qt ${SOURCE_FILES_QT})
target_link_libraries(othello-qt ${Qt5Widgets_LIBRARIES})
