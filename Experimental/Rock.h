#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "ObjectManager.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	
public:
	Rock();
	~Rock();
	void initialise(ObjectManager* pObjectManager, Vector2D startPosition, Vector2D startVelocity, float imageSize);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void SpawnRock(Vector2D position);
	Vector2D getPosition();
	float GetImageSize();
};

