cmake_minimum_required(VERSION 3.3)
project(othello)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic ")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

#------------Only command line
set(SOURCE_FILES_CLI GameBoard.cc MainGame.cc GameLogic.cc Player.cc AI.cc main.cc)
add_executable(othello-cli ${SOURCE_FILES_CLI})


#-------------And with GUI

find_package (Qt5Widgets)

set (othelloLib_src AI.cc GameBoard.cc GameLogic.cc MainGame.cc OthelloGui.cc Player.cc
    PlayerSelection.cc BoardGraphics.cc InfoPanel.cc StartPanel.cc EndScreen.cc HistoryItemGui.cc
    HistoryPanel.cc)
set(othelloLib_hdr OthelloGui.hh PlayerSelection.hh BoardGraphics.hh InfoPanel.hh StartPanel.hh
    EndScreen.hh HistoryItemGui.hh HistoryPanel.hh)

set(othelloLib_ui OthelloGui.ui PlayerSelection.ui InfoPanel.ui StartPanel.ui EndScreen.ui
    HistoryItemGui.ui HistoryPanel.ui)
set (othelloBin_src main-qt.cc)

qt5_wrap_cpp(othelloLib_hdr_moc ${othelloLib_hdr})
qt5_wrap_ui (othelloLib_ui_moc  ${othelloLib_ui})

SOURCE_GROUP("moc_files" FILES ${otelloLib_hdr_moc})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (othelloLib SHARED 
    ${othelloLib_src}
    ${othelloLib_hdr_moc}
    ${othelloLib_ui_moc}
)
target_link_libraries (othelloLib Qt5::Widgets)

add_executable(othello ${othelloBin_src})
target_link_libraries (othello othelloLib)


