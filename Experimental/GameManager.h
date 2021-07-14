#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidArcadeMachine.h"

class GameManager : public GameObject
{
private:
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	GameManager* pGameManager;

public:
	GameManager();
	~GameManager();
	void initialise(ObjectManager* pObjectManager, GameManager* pGameManager);
	void render();
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void Deactivate();
};

