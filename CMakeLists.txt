# CMakeList.txt : 顶级 CMake 项目文件，执行全局配置
# 和此处的包含子项目。
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project ("AskMalt")

include_directories(include/)

set(SrcPath src/main.cpp include/Value.h include/Predefined.h include/Function.h src/Object/Function.cpp include/Objects.h src/Object/Objects.cpp
include/Parser/Token.h include/Parser/Lexer.h src/Parser/Token.cpp src/Parser/Lexer.cpp include/Parser/AST.h src/Parser/AST.cpp src/Parser/Parser.cpp)

set(ExecName malt)

#add_library(lib${ExecName} ${SrcPath})

add_executable(${ExecName} ${SrcPath})

