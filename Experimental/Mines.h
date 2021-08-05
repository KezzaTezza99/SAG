#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidsLevelManager.h"

class Mines : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	AsteroidsLevelManager* pLevelManager;

public:
	Mines();
	~Mines();
	void initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager, Vector2D startPosition, Vector2D startVelocity);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	Vector2D getPosition();
};

