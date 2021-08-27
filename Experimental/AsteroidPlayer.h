//Author: w18024358
//Purpose: The purpose of this class is to provide a playable character to the user who can interact with the 
//Asteroid Mini Game. The player will be able to move, shoot and collide with other entities in the Mini Game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidsLevelManager.h"

class AsteroidPlayer: public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;	
	ObjectManager* pObjectManager;					//Need to be able to create bullets and Explosions
	AsteroidsLevelManager* pLevelManager;			//Used to tell the Level Manager when the Player dies
	float shootDelay;								//Used to stop the Player from being able to Infinetly shoot
	Circle2D collisionShape;
	float RockImageSize;							//Used for differnet collisions based on the Asteroid Size
public:
	AsteroidPlayer();
	void Initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};


