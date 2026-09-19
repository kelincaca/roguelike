#include<raylib.h>
#include"gameMain.h"
bool initGame()
{
    return true;
}
bool updateGame()
{
     Color c;
        c.r=255;
        c.g=0;
        c.b=200;
        c.a=255;
        DrawText("Wow!raylib!",100,100,30,BLACK);
    return true; 
}
void closeGame()
{
}