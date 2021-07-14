#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidsLevelManager.h"
#include "GameManager.h"

class AsteroidArcadeMachine: public GameObject
{
private:
	ObjectManager* pObjectManager;
	//SpaceInvadersArcadeMachine* pSpaceInvaders;
	Circle2D collisionShape;
	bool startMiniGame;
	
public:
	AsteroidArcadeMachine();
	~AsteroidArcadeMachine();
	void initialise(ObjectManager* pObjectManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void SetActivity();
	void Deactivate();
};