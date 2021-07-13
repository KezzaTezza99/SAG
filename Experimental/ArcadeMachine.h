#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidsLevelManager.h"

class ArcadeMachine: public GameObject
{
private:
	ObjectManager* pObjectManager;
	Circle2D collisionShape;
	bool startMiniGame;
	
public:
	ArcadeMachine();
	~ArcadeMachine();
	void initialise(ObjectManager* pObjectManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void SetActivity();
	void Deactivate();
};