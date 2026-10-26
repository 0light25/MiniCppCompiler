@echo off

echo Compiling MiniCppCompiler...

g++ -std=c++11 -Iinclude src/main.cpp src/lexer.cpp src/parser.cpp src/ast.cpp src/symbol_table.cpp -o compiler.exe

if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

echo Compilation successful!

if "%~1"=="" (
    echo Error: Please provide a program file!
    exit /b 1
)

if not exist "%~1" (
    echo Error: Program file not found: %~1
    exit /b 1
)

compiler.exe "%~1"