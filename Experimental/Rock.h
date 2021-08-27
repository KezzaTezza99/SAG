//Author: w18024358
//Purpose: The purpose of this class is to add Asteroids to the Asteroid Mini Game 
//the rocks will be used to increase the Player's score as well as adding an objective to the game / goal
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidsLevelManager.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	AsteroidsLevelManager* pLevelManager;
public:
	Rock();
	void Initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager, 
		Vector2D startPosition, Vector2D startVelocity, float imageSize = 1.0f);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void SpawnRock(Vector2D position);
};