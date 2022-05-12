cmake_minimum_required(VERSION 3.21)
project(tryap)

set(CMAKE_CXX_STANDARD 17)

add_executable(tryap main.cpp RegularExpression/RegularExpression.cpp RegularExpression/RegularExpression.h RegularGrammar/RegularGrammar.cpp RegularGrammar/RegularGrammar.h Grammar/Grammar.cpp Grammar/Grammar.h AttributeGrammar/AttributeGrammar.cpp AttributeGrammar/AttributeGrammar.h ContextFreeGrammar/ContextFreeGrammar.cpp ContextFreeGrammar/ContextFreeGrammar.h LLGrammar/LLGrammar.cpp LLGrammar/LLGrammar.h Authomat/Authomat.cpp Authomat/Authomat.h AttributeGrammar/Tree.cpp AttributeGrammar/Tree.h TinyXml/tinyxml2.cpp TinyXml/tinyxml2.h)
