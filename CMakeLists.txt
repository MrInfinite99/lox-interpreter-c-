cmake_minimum_required(VERSION 3.10)

project(LoxInterpreter)

#add_executable(LoxInterpreter main.cpp parser.cpp scanner.cpp token.cpp lox.cpp)

# Add header files
set(HEADERS
    header/astPrinter.h
    header/Expr.h
    header/lox.h 
    header/parser.h 
    header/scanner.h 
    header/token.h 
    header/TokenType.h 
)

# Add source files
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/scanner.cpp 
    src/token.cpp 
    src/lox.cpp
)

set(CMAKE_CXX_STANDARD 17)

# Add Executable
add_executable(LoxInterpreter ${SOURCES} ${HEADERS})

#target_include_directories(MySFMLProject PRIVATE ${CMAKE_SOURCE_DIR}/header)