set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.2)
project(MineSweeper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Board.cpp Board.h Tile.cpp Tile.h GameObject.cpp GameObject.h Interactable.cpp Interactable.h)
add_executable(MineSweeper ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MineSweeper ${SFML_LIBRARIES})
endif()