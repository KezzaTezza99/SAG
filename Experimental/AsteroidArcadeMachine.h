//Author: w18024358
//Purpose: Placing a asteroid arcade machine that when the player collides with
//starts the asteroids mini game

#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class AsteroidArcadeMachine: public GameObject
{
private:
	ObjectManager* pObjectManager;
	Circle2D collisionShape;
	bool startMiniGame;								//Used to start Mini Game
public:
	AsteroidArcadeMachine();
	void Initialise(ObjectManager* pObjectManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};