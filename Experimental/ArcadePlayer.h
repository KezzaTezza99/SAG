#pragma once
#include "GameObject.h"
#include "GameManager.h"
#include "AsteroidArcadeMachine.h"
#include "SpaceInvadersArcadeMachine.h"

class ArcadePlayer : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	Vector2D acceleration;
	GameManager* pGameManager;		//Used to Delete Level Manager / Game Manager on Mini Game Start Up
	//Used so the Player can remove the correct mini game when the user selects one to play
	AsteroidArcadeMachine* pAsteroids;
	SpaceInvadersArcadeMachine* pSpaceInvaders;

public:
	ArcadePlayer();
	~ArcadePlayer();
	void initialise(GameManager* pGameManager, AsteroidArcadeMachine* pAsteroids, SpaceInvadersArcadeMachine* pSpaceInvaders);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};