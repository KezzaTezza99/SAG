#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class GameManager : public GameObject
{
private:
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
public:
	GameManager();
	~GameManager();
	void initialise(ObjectManager* pObjectManager);
	void render();
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void Deactivate();
};

