cmake_minimum_required(VERSION 3.13)
project(Grammars)

set(CMAKE_CXX_STANDARD 14)

add_executable(Grammars main.cpp Variable.cpp Variable.h Terminal.cpp Terminal.h Rule.cpp Rule.h NonTerminal.cpp NonTerminal.h StringManager.cpp StringManager.h Grammar.cpp Grammar.h GrammarManager.cpp GrammarManager.h)