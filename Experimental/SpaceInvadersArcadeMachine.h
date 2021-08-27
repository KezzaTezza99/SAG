//Author: w18024358
//Purpose: The purpose of this class is to spawn a interactable Bitmap to the Player and when the player collides 
//with the machine it will spawn the Space Invader Level Manager and start the Mini Game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class SpaceInvadersArcadeMachine : public GameObject
{
private:
	ObjectManager* pObjectManager;
	Circle2D collisionShape;
	bool startSpaceInvaders;						//Flag to see if the Player collides with Space Invader Mini Game
public:
	SpaceInvadersArcadeMachine();
	void Initialise(ObjectManager* pObjectManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};