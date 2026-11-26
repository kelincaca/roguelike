#include"slime.h"
#include<assetManager.h>
#include"helpers.h"
#include<randomStuff.h>


void Slime::render(AssetManager& assetManager)
{
	auto aabb = getRectangleForEntity(physics.transform, 1, 1);

	DrawTexturePro(
		assetManager.slime,
		getTextureAtlas(0, 0, 32, 32),
		aabb,
		{ 0,0 },
		0.0f,
		WHITE
	);
}

void Slime::update(float deltaTime)
{
	changeStateTimer -= deltaTime;

	if (changeStateTimer < 0)
	{
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
}