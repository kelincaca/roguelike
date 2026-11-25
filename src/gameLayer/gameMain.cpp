#include<raylib.h>
#include"gameMain.h"
#include<cassert>
#include"assetManager.h"
#include"gameMap.h"
#include"helpers.h"
#include <raymath.h>
struct GameData
{
	GameMap gameMap;
	Camera2D camera;
}gameData;

AssetManager assetManager;

bool initGame()
{
	assetManager.loadAll();

	gameData.gameMap.create(700, 500);
	for(int i=0;i<700;i++)
		for (int j = 0;j < 500;j++)
		{
			gameData.gameMap.getBlockUnsafe(i, j).type = Block::stone;
		}
	gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
	gameData.gameMap.getBlockUnsafe(1, 1).type = Block::grass;
	gameData.gameMap.getBlockUnsafe(2, 2).type = Block::goldBlock;
	gameData.gameMap.getBlockUnsafe(3, 3).type = Block::glass;
	gameData.gameMap.getBlockUnsafe(4, 4).type = Block::platform;
	gameData.camera.target = { 0,0 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 100.0f;

	return true;
}
bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }
	gameData.camera.offset = { GetScreenWidth()/2.0f,GetScreenHeight() / 2.0f };
	ClearBackground({ 75,75,150,225 });

	if (IsKeyDown(KEY_LEFT))gameData.camera.target.x -= 7.f * deltaTime;
	if (IsKeyDown(KEY_RIGHT))gameData.camera.target.x += 7.f * deltaTime;
	if (IsKeyDown(KEY_UP))gameData.camera.target.y -= 7.f * deltaTime;
	if (IsKeyDown(KEY_DOWN))gameData.camera.target.y += 7.f * deltaTime;
	BeginMode2D(gameData.camera);

	Vector2 topLeftView = GetScreenToWorld2D({ 0,0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({ (float)GetScreenWidth(),(float)GetScreenHeight() }, gameData.camera);

	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x + 1);
	int startYView = (int)floorf(topLeftView.y - 1);
	int endYView = (int)ceilf(bottomRightView.y + 1);

	startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
	endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);
	startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
	endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);
	for (int y = startYView;y <=endYView;y++)
		for (int x = startXView;x <=endXView;x++)
		{
			auto& b = gameData.gameMap.getBlockUnsafe(x, y);

			if (b.type != Block::air)
			{
				DrawTexturePro(
					assetManager.textures,
					getTextureAtlas(b.type, 0, 32, 32),
					{(float)x,(float)y,1,1},
					{ 0,0 },
					0.0f,
					WHITE
				);
			}
		}

	EndMode2D();

	DrawFPS(10, 10);
	return true;
}
void closeGame()
{
}