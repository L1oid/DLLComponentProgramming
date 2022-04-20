echo off

@REM pause
@REM exit

"C:\Program Files\CodeBlocks\MinGW\bin\g++" -c ./source/ServersDLL.cpp -o ./build/ServersDLL.o
"C:\Program Files\CodeBlocks\MinGW\bin\g++" -shared ./build/ServersDLL.o -o ./build/ServersDLL.dll -Wl,--kill-at

@REM pause
@REM exit

"C:\Program Files\CodeBlocks\MinGW\bin\g++" -c ./source/Main.cpp -o ./build/Main.o

"C:\Program Files\CodeBlocks\MinGW\bin\g++" ./build/Main.o -o ./build/run.exe

pause
exit