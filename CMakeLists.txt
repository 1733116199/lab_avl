cmake_minimum_required(VERSION 2.8.4)
set(name testavl)
project(${name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(${name} COMMAND make -C ${${name}_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})

add_executable(lab_avl_2
        avltree.cpp
        avltree.h
        avltree_given.cpp
        coloredout.cpp
        coloredout.h
        main.cpp
        Makefile
        printtree.h
        soln_testavl.out)
