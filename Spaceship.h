#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"

class Spaceship
{
private:
	float angle;
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D friction;
	PictureIndex image;

public:
	Spaceship();
	void initialise();
	void render();
	void update();
};

