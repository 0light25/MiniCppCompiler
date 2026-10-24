
# Mini C++ Compiler

A compiler front-end and interpreter for a subset of the C++ language, implemented from scratch in C++11.

## Overview

MiniCppCompiler demonstrates how source code is transformed through lexical analysis, parsing, abstract syntax tree (AST) construction, semantic analysis, and execution.

The project was developed over 30 days to understand compiler design and implementation.

## Features

- Lexical analysis and token generation
- Recursive-descent parsing
- Abstract Syntax Tree (AST)
- Arithmetic expressions and operator precedence
- Variable declarations and assignments
- Comparison operators
- If-else conditional statements
- While loops
- Symbol table management
- Scope and semantic validation
- Type checking
- Expression evaluation and variable storage
- Syntax and semantic error detection
- Automated tests

## Technologies

- C++11
- STL
- GNU g++ Compiler
- Git and GitHub

## Project Structure

MiniCppCompiler/
  include/
    lexer.h
    parser.h
    ast.h
    symbol_table.h

  src/
    main.cpp
    lexer.cpp
    parser.cpp
    ast.cpp
    symbol_table.cpp

  tests/
    lexer_tests.cpp
    parser_test.cpp
    error_tests.cpp
    semantic_tests.cpp
    type_tests.cpp
    variable_tests.cpp
    end_to_end_tests.cpp

  examples/
    program.mc

  README.md
  .gitignore

## Architecture

Source Code
    |
    v
Lexer
    |
    v
Tokens
    |
    v
Parser
    |
    v
Abstract Syntax Tree
    |
    v
Semantic Analysis
    |
    v
AST Evaluation
    |
    v
Execution Result

## Example Program

```cpp
int x = 10;
x = x + 5;

int y = x * 2;
```

Expected final variable values:

```text
x = 15
y = 30
```

## Build Instructions

Requirements:
- C++11-compatible compiler
- g++

Compile from the project root:

```bash
g++ -std=c++11 -Iinclude src/main.cpp src/lexer.cpp src/parser.cpp src/ast.cpp src/symbol_table.cpp -o compiler
```

Run on Windows:

```bat
compiler.exe examples/program.mc
```

## End-to-End Testing

Compile:

```bash
g++ -std=c++11 -Iinclude tests/end_to_end_tests.cpp src/lexer.cpp src/parser.cpp src/ast.cpp src/symbol_table.cpp -o end_to_end_tests
```

Run on Windows:

```bat
end_to_end_tests.exe
```

The project includes tests for syntax analysis, semantic validation, type checking, variable execution, and integrated language behavior.

## Error Handling

The project can detect errors such as:

- Missing semicolons
- Invalid expressions
- Missing closing parentheses or braces
- Undeclared variables
- Duplicate declarations
- Type mismatches
- Undefined variable access during execution

## Limitations

This implementation supports a limited C++-like language rather than the complete C++ standard.

It currently uses AST evaluation to execute programs; it does not generate machine code or executable binaries from input programs.

## Future Improvements

- Function declarations and calls
- For loops
- Arrays
- Additional data types
- Improved error messages with line numbers
- Intermediate representation
- LLVM or assembly code generation

## Learning Outcomes

- Compiler architecture
- Recursive-descent parsing
- AST construction and traversal
- Symbol tables and scope handling
- Type validation
- Runtime evaluation
- Error handling and testing

## Author

Developed as a 30-day compiler design learning project.

