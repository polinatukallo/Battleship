cmake_minimum_required(VERSION 3.10)
project(battleship)

set(CMAKE_CXX_STANDARD 17) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(parser)
include_directories(game)

add_executable(battleship
    main.cpp
    parser/command.cpp
    parser/command.h
    parser/commandFactory.h

    game/field.cpp
    game/field.h
)
