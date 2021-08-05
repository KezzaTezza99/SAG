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
	~SpaceInvaderPlayer();
	void initialise(ObjectManager* pObjectManager, SpaceInvaderLevelManager* pLevelManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

