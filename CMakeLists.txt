cmake_minimum_required(VERSION 3.21)
project(tryap)

set(CMAKE_CXX_STANDARD 17)

add_executable(tryap main.cpp RegularExpression/RegularExpression.cpp RegularExpression/RegularExpression.h RegularGrammar/RegularGrammar.cpp RegularGrammar/RegularGrammar.h Grammar/Grammar.cpp Grammar/Grammar.h)
