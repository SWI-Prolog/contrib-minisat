cmake_minimum_required(VERSION 2.8.12)
project(swipl-minisat)

include("../cmake/PrologPackage.cmake")

if(0)
swipl_plugin(
    minisat
#   C_SOURCES minisat/minisat/core/Solver.cc C/pl-minisat.C
    C_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/minisat
		  ${CMAKE_CURRENT_SOURCE_DIR}/../cpp
    PL_LIBS cnf.pl minisat.pl)

else()

swipl_plugin(
    minisat
    C_SOURCES C/Solver.C C/pl-minisat.C
    C_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/C
		  ${CMAKE_CURRENT_SOURCE_DIR}/../cpp
    PL_LIBS cnf.pl minisat.pl)
endif()

swipl_examples(examples/adder.pl examples/pearl_examples.pl)
