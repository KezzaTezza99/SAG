//Author: w18024358
//Purpose: Creates an Enemy Ship that will endlessly chase the player and is used in the 
//Hunted Mini Game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "HuntedPlayer.h"
#include "ParticleSystem.h"
#include "HuntedLevelManager.h"

class EnemyShip: public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;
	ObjectManager* pObjectManager;					//Needs to create bullets, explosions and particles
	HuntedLevelManager* pLevelManager;				//Needed to tell the Level Manager when they have been destroyed
	HuntedPlayer* pThePlayer;						//Needs to know the Player's Position to chase them
	ParticleSystem* pParticles;						//Needs reference of Particle System to enhance Explosions
	Circle2D collisionShape;
	float shootDelay;								//Needs a timer to stop the enemy spam shooting the Player constantly
	float countDown;								//A timer before the Enemy can shoot the Player
													//Otherwise as soon as they spawn they shoot
public:
	EnemyShip();
	void Initialise(ObjectManager* pObjectManager, HuntedLevelManager* pLevelManager, HuntedPlayer* pThePlayer, Vector2D randomStartPosition, ParticleSystem* pParticles);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

