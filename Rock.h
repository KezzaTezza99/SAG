#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;

public:
	Rock();
	void initialise(Vector2D startPosition, Vector2D startVelocity);
	void update(float frameTime);
};

