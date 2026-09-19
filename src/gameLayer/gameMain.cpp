#include<raylib.h>
#include"gameMain.h"
struct GameData
{
    float positionX = 100;
    float positionY = 100;
}gameData;
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
        c.a = 255;
        if (IsKeyDown(KEY_A)) { gameData.positionX -= 1; }
        if (IsKeyDown(KEY_D)) { gameData.positionX += 1; }
        if (IsKeyDown(KEY_W)) { gameData.positionY -= 1; }
        if (IsKeyDown(KEY_S)) { gameData.positionY += 1; }
        //positionX,positionY,sizeX,sizeY,color
        DrawRectangle(gameData.positionX, gameData.positionY, 50, 50, c);
    return true; 
}
void closeGame()
{
}