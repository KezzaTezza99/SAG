#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "AsteroidArcadeMachine.h"
//TODO
//MAKE THE GAME MANAGER DELETE BOTH MINI GAMES

class SpaceInvadersArcadeMachine : public GameObject
{
private:
	ObjectManager* pObjectManager;
	Circle2D collisionShape;
	bool startSpaceInvaders;
	//AsteroidArcadeMachine* pAsteroids;
public:
	SpaceInvadersArcadeMachine();
	~SpaceInvadersArcadeMachine();
	void initialise(ObjectManager* pObjectManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

