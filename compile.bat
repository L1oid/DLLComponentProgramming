echo off

@REM pause
@REM exit

g++ -c ./source/ServersDLL.cpp -o ./build/ServersDLL.o
g++ -shared ./build/ServersDLL.o -o ./build/ServersDLL.dll -Wl,--kill-at

@REM pause
@REM exit

g++ -c ./source/Main.cpp -o ./build/Main.o

g++ ./build/Main.o -o ./build/run.exe

pause
exit