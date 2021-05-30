#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;

public:
	Rock();
	~Rock();
	void initialise(Vector2D startPosition, Vector2D startVelocity);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();

	Vector2D getPosition();
};

