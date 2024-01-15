copy ..\lib\libinternalfield.dll libinternalfield.dll


@echo off
setlocal enabledelayedexpansion

:: Compiler options
set "CFLAGS=-std=c++17 -O3"

:: Library and include paths
set "LDFLAGS=-L ..\lib -linternalfield -lm"
set "IFLAGS=-I ..\include"

:: Compiler commands
set "CC=g++ %CFLAGS%"
set "CCo=g++ -c %CFLAGS%"

:: Detect the operating system (Linux or Windows)
for /f %%i in ('uname -s 2^>nul') do set OS=%%i

:: Define the executable file extensions
if "%OS%"=="Linux" (
    set "EXE="
) else (
    set "EXE=.exe"
)

:: Build targets
%CCo% %IFLAGS% testdata.cc -o testdata.o
%CC% %IFLAGS% testdata.o test.cc -o test%EXE% %LDFLAGS%
%CC% %IFLAGS% timer.cc -o timer%EXE% %LDFLAGS%
gcc %IFLAGS% ctest.c -o ctest%EXE% %LDFLAGS%
%CC% %IFLAGS% cpptest.cc -o cpptest%EXE% %LDFLAGS%

:: Run tests
@.\test%EXE%
@.\ctest%EXE%
@.\cpptest%EXE%
@.\timer%EXE%


del /F /Q test%EXE%
del /F /Q timer%EXE%
del /F /Q ctest%EXE%
del /F /Q cpptest%EXE%
del /F /Q libinternalfield.dll
for %%f in (*.o) do (
    del "%%f"
)