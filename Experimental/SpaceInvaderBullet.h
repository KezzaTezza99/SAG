//Author: w18024358
//Purpose: Another bullet class that will just be used by the Space Invader, this a quick work around
//to stop Enemies killing one another. The one benefit of not using the Bullet class from another Mini Game
//is the slight benefit of decoupled code, yes the code is duplicated but it does not have to know about 
//the other mini games and other entities it is encapsulated into this mini game
#pragma once
#include "GameObject.h"

//Would be better to either Inherit from one Bullet Class or make bullet.h multifunctional for different purposes
class SpaceInvaderBullet : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	float lifeTime;									//A timer that is used to Deactivate the bullets
public:
	SpaceInvaderBullet();
	void Initialise(Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

