//Author: w18024358
//Purpose: The purpose of this class is to provide the user with a playerable character for the Space Invader Mini Game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SpaceInvaderLevelManager.h"

class SpaceInvaderPlayer : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D friction;
	ObjectManager* pObjectManager;
	SpaceInvaderLevelManager* pLevelManager;
	float shootDelay;
public:
	SpaceInvaderPlayer();
	void Initialise(ObjectManager* pObjectManager, SpaceInvaderLevelManager* pLevelManager, Vector2D startPosition);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

