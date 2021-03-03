#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Player: public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;

public:
	Player();
	void initialise();
	void update(float frameTime);
};

