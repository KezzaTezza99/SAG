#pragma once
#include "GameObject.h"

class Stars : public GameObject
{
private:
	Circle2D collisionShape;
public:
	Stars();
	void initialise(Vector2D startPosition);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

