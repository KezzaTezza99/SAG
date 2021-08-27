//Author: w18024358
//Purpose: The purpose of the mines are to add a little more complexity and challenge to the Asteroids Mini Game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidsLevelManager.h"

class Mines : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	AsteroidsLevelManager* pLevelManager;			//Needed so mine can inform level manager of its death
public:
	Mines();
	void Initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager, Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

