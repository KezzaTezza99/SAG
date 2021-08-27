//Author: w18024358
//Purpose: The purpose of this class is to simpily add some visual effects to enhance the game 
//as well as providing something to visually show the Player that they are moving around the 
//terrain in the Hunted Game Mode
#pragma once
#include "GameObject.h"

class Stars : public GameObject
{
private:
	Circle2D collisionShape;
public:
	void Initialise(Vector2D startPosition);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};