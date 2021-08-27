//Author: w18024358
//Purpose: The purpose of this class is to provide the User with a playable character in the Hunted Mini Game
//this player has a different class for a quick and easy soloution to decoupling as this player doesnt need to 
//know about the other Mini Games entities etc 
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "ParticleSystem.h"

class HuntedPlayer : public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;
	ObjectManager* pObjectManager;
	ParticleSystem* pParticles;
	Circle2D collisionShape;
	float boostTimer;								//Used to stop the Player endessly boosting
	float shootDelay;								//Stops the player being able to rapidly fire bullets
public:
	HuntedPlayer();
	void Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

