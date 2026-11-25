#include<raylib.h>
#include"gameMain.h"
#include<cassert>
#include"assetManager.h"
#include"gameMap.h"
#include"helpers.h"
#include"physics.h"
#include <raymath.h>
struct GameData
{
	GameMap gameMap;
	Camera2D camera;
	PhysicalEntity player;
}gameData;

AssetManager assetManager;

bool initGame()
{
	assetManager.loadAll();

	gameData.gameMap.create(10, 8);
	for (int y = 0;y < gameData.gameMap.h;y++)
		for (int x = 0;x < gameData.gameMap.w;x++)
		{
			if (x == 0 || x == gameData.gameMap.w - 1 || y == 0 || y == gameData.gameMap.h - 1)
			{
				gameData.gameMap.getBlockUnsafe(x, y).type = Block::stone;
			}
			else
			{
				gameData.gameMap.getBlockUnsafe(x, y).type = Block::dirt;
			}
		}
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 100.0f;

	gameData.player.teleport({5,4});
	gameData.player.transform.w = 0.6f;
	gameData.player.transform.h = 0.6f;

	return true;
}
bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }
	gameData.camera.offset = { GetScreenWidth()/2.0f,GetScreenHeight() / 2.0f };
	ClearBackground({ 75,75,150,225 });

	static float CAMERA_SPEED = 10;
	if (IsKeyDown(KEY_A))gameData.player.transform.pos.x -= CAMERA_SPEED * GetFrameTime();
	if (IsKeyDown(KEY_D))gameData.player.transform.pos.x += CAMERA_SPEED * GetFrameTime();
	if (IsKeyDown(KEY_W))gameData.player.transform.pos.y -= CAMERA_SPEED * GetFrameTime();
	if (IsKeyDown(KEY_S))gameData.player.transform.pos.y += CAMERA_SPEED * GetFrameTime();

	gameData.player.updateForces(deltaTime);
	gameData.player.resolveConstrains(gameData.gameMap);
	gameData.camera.target = gameData.player.transform.pos;
	gameData.player.updateFinal();
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

	Transform2D playerSprite = gameData.player.transform;
	playerSprite.w = 0.6;
	playerSprite.h = 0.8;
	DrawTexturePro(
		assetManager.player,
		{ 0,0,(float)assetManager.player.width,(float)assetManager.player.height },
		playerSprite.getAABB(),
		{ 0,0 },
		0.0f,
		WHITE
	);

	DrawRectangleLinesEx(gameData.player.transform.getAABB(), 0.1,
		{ 20,101,250,120 });
	EndMode2D();

	DrawFPS(10, 10);
	return true;
}
void closeGame()
{
}