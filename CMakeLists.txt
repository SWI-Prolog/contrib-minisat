cmake_minimum_required(VERSION 2.8.12)
project(swipl-minisat)

include("../cmake/PrologPackage.cmake")

swipl_plugin(
    minisat
    C_SOURCES C/Solver.C C/pl-minisat.C
    PL_LIBS cnf.pl minisat.pl)

swipl_examples(examples/adder.pl examples/pearl_examples.pl)
