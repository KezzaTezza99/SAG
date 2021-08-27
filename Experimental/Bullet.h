//Author: w18024358
//Purpose: To create a Bullet that will be used by the Player, the bullet will hanlde 
//collisons with enemies
#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float lifeTime;									//This is so we can delete the bullet after a few seconds
	Circle2D collisionShape;
public:
	Bullet();
	void Initialise(Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void DrawCollision();
	void HandleCollision(GameObject& other);
};

