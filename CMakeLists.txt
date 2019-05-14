cmake_minimum_required( VERSION 3.0 )
project( MON_PROJET )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra" )

add_executable( main.out main.cpp game.cpp )
