@echo off
g++ main.cpp gameLayer/gameMain.cpp -o main -Iinclude -Llib -lraylib -lgdi32 -lwinmm
if %errorlevel% equ 0 (
    echo 编译成功，启动程序
    main.exe
) else (
    echo 编译出错
)
