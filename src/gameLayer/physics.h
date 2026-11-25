#pragma once

#include<raylib.h>
#include<raymath.h>

struct Transform2D
{
	Vector2 pos = {};
	float w = 0;
	float h = 0;
	Vector2 getCenter() const { return { pos.x,pos.y }; }
	Vector2 getTop() const { return { pos.x,pos.y-h*0.5f }; }
	Vector2 getBottom() const { return { pos.x,pos.y+h*0.5f }; }
	Vector2 getLeft() const { return { pos.x-w*0.5f,pos.y }; }
	Vector2 getRight() const { return { pos.x+w*0.5f,pos.y }; }
	Vector2 getTopLeft() const { return { pos.x-w*0.5f,pos.y -h*0.5f}; }
	Vector2 getTopRight() const { return { pos.x+2*0.5f,pos.y-h*0.5f }; }
	Vector2 getBottomLeft() const { return { pos.x-w*0.5f,pos.y+h*0.5f }; }
	Vector2 getBottomRight() const { return { pos.x+w*0.5f,pos.y-h*0.5f }; }

Rectangle getAABB()
{
	return { pos.x - w * 0.5f,pos.y - h * 0.5f,w,h };
}

bool intersectPoint(Vector2 point, float delta = 0)
{
	Rectangle aabb = getAABB();
	aabb.x -= delta;
	aabb.y -= delta;
	aabb.width += 2 * delta;
	aabb.height += 2 * delta;

	return CheckCollisionPointRec(point, aabb);
}
bool intersectTransform(Transform2D other, float delta = 0)
{
	Rectangle a = getAABB();
	Rectangle b = other.getAABB();
	a.x -= delta;
	a.y -= delta;
	a.width += 2 * delta;
	a.height += 2 * delta;
	b.x -= delta;
	b.y -= delta;
	b.width += 2 * delta;
	b.height += 2 * delta;


	return CheckCollisionRecs(a, b);
}
};
struct GameMap;
struct PhysicalEntity
{
	Transform2D transform;
	Vector2 lastPosition = {};
	Vector2 velocity = {};
	bool upTouch = 0;
	bool downTouch = 0;
	bool leftTouch = 0;
	bool rightTouch = 0;
	void teleport(Vector2 pos)
	{
		transform.pos = pos;
		lastPosition = pos;
	}
	void updateForces(float deltaTime)
	{
		transform.pos += velocity * deltaTime;
	}
	void updateFinal()
	{
		lastPosition = { transform.pos.x,transform.pos.y };
	}
	Vector2& getPosition()
	{
		return transform.pos;
	}
	void resolveConstrains(GameMap& mapData);
	void checkCollisionOnce(Vector2& pos, GameMap& mapData);
	Vector2 performCollisionOnOneAxis(GameMap& mapData, Vector2 pos, Vector2 delta);
}; 