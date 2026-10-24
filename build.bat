@echo off
setlocal

echo Compiling MiniCppCompiler...

g++ -std=c++11 -Iinclude src/*.cpp -o compiler.exe

if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

echo Compilation successful!

if "%~1"=="" (
    set /p "program=Enter program file path: "
) else (
    set "program=%~1"
)

if not exist "%program%" (
    echo Error: Program file not found!
    exit /b 1
)

echo Running %program%...
compiler.exe "%program%"
