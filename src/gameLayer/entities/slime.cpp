#include"slime.h"
#include<assetManager.h>
#include"helpers.h"
#include<randomStuff.h>


void Slime::render(AssetManager& assetManager)
{
	auto aabb = getRectangleForEntity(physics.transform, 1, 1);

	DrawTexturePro(
		assetManager.slime,
		getTextureAtlas(animation.positionX, animation.positionY, 32, 32),
		aabb,
		{ 0,0 },
		0.0f,
		WHITE
	);
}

void Slime::update(float deltaTime,std::ranlux24_base& rng,Vector2 playerPosition)
{
	changeStateTimer -= deltaTime;

	if (changeStateTimer < 0)
	{
		if (Vector2Length(physics.velocity) > 0.01f)
		{
			animation.setAnimation(1);
		}
		else
		{
			animation.setAnimation(0);
		}
		changeStateTimer = getRandomFloat(rng, 1, 7);

		float distanceToPlayer = Vector2Distance(playerPosition, getPosition());

		if (distanceToPlayer < 20)
		{
			if (getRandomChance(rng, 0.8))
			{
				currentState = STATE_CHASING;
			}
			else
			{
				currentState = STATE_WONDERING;
			}
		}
		else
		{
			currentState = STATE_WONDERING;
		}
	}

	switch (currentState)
	{
	case STATE_WONDERING:
	{
		physics.velocity = {};
	}
		break;

	case STATE_CHASING:
	{
		Vector2 direction = playerPosition - getPosition();
		float distance = Vector2Length(direction);

		if (distance > 0.1f)
		{
			physics.velocity =
				Vector2Normalize(direction) * 2.0f;
		}
		else
		{
			physics.velocity = {};
		}
	}
	break;
	}
	animation.update(deltaTime, 0.08, 7);
}