//Author: w18024358
//Purpose: The purpose of this class is to place a bitmap on screen for when the Player collides with
//can create the Hunted Level Manager anc start the Mini Game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "ParticleSystem.h"

//Hunted will just be a basic survival game
//player will be endlessly chased and needs to survive, game ends when Player dies - incomplete
class HuntedArcadeMachine : public GameObject
{
private:
	ObjectManager* pObjectManager;					
	ParticleSystem* pParticles;						//Needs to pass Particle System to Relevant Objects
	Circle2D collisionShape;
	bool startHunted;								//Flag to remove the arcade machine from the game when mini game starts
public:
	HuntedArcadeMachine();
	void Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles);
	void Update(float frameTime);
	IShape2D& GetShape();
	void DrawCollision();
	void HandleCollision(GameObject& other);
};

