//Author: w18024358
//Purpose: This class will be used for managing the Space Invader Mini Game
//like previous level managers it will be responsible for tracking score, lives and starting 
//the next level / ending the game
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "SpaceInvaderFormation.h"
#include "SpaceInvaderLevelManager.h"

class SpaceInvadeEnemy : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;					//Needed to create bullets
	SpaceInvaderFormation* pFormation;				//Needed for the Enemies to move in a Formation
	SpaceInvaderLevelManager* pLevelManager;		//When a Enemy dies tell the Level Manager
	Vector2D offset;								//Offset to ensure that Enemies are spaced apart + follow formation
	float randomShootDelay;							//A random time to decide how often each Enemy shall shoot 
public:
	SpaceInvadeEnemy();
	void Initialise(ObjectManager* pObjectManager, Vector2D offset, SpaceInvaderFormation* pFormation,
					SpaceInvaderLevelManager* pLevelManager);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};