#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SpaceInvaderFormation.h"
#include "SpaceInvaderLevelManager.h"

class SpaceInvadeEnemy : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	Vector2D offset;
	float shootDelay;
	SpaceInvaderFormation* pFormation;
	SpaceInvaderLevelManager* pLevelManager;

public:
	SpaceInvadeEnemy();
	~SpaceInvadeEnemy();
	void initialise(ObjectManager* pObjectManager, Vector2D offset, SpaceInvaderFormation* pFormation,
					SpaceInvaderLevelManager* pLevelManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

