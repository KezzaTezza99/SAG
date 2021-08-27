//Author: w18024358
//Purpose: To create a player that can walk around the arcade and interact with the machines
//to start the mini game, at the moment this is a placeholder and is not complete

#pragma once
#include "GameObject.h"
#include "GameManager.h"
#include "AsteroidArcadeMachine.h"
#include "SpaceInvadersArcadeMachine.h"
#include "HuntedArcadeMachine.h"

class ArcadePlayer : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	Vector2D acceleration;
	GameManager* pGameManager;						//Used to Delete Level Manager / Game Manager on Mini Game Start Up
													//Used so the Player can remove the correct mini game when 
													//the user selects one to play
	AsteroidArcadeMachine* pAsteroids;				//Needed so can delete from game 
	SpaceInvadersArcadeMachine* pSpaceInvaders;		//Needs to be deleted again once the real games start
	HuntedArcadeMachine* pHunted;					//Needed so it can be removed from "Arcade"

public:
	ArcadePlayer();
	void Initialise(GameManager* pGameManager, AsteroidArcadeMachine* pAsteroids, 
					SpaceInvadersArcadeMachine* pSpaceInvaders, HuntedArcadeMachine* pHunted);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};