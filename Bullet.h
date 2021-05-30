#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float lifeTime;		//This is so we can delete the bullet after a few seconds
	Circle2D collisionShape;

public:
	Bullet();
	~Bullet();
	void initialise(Vector2D startPosition, Vector2D startVelocity);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

