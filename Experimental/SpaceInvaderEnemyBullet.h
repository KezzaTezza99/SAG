//Author: w18024358
//Purpose: The purpose of this bullet is to be used by the Enemy to only kill the Player and not each other
#pragma once
#include "GameObject.h"

//Temporary Class to stop space invaders shooting one another
//if time permits will tackle this issue and ensure the enemies only shoot if they have a free line of fire
//which will resolve issues with them killing each other 
//quick temp fix
class SpaceInvaderEnemyBullet : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	float lifeTime;									//When the timer reaches 0 the bullets will be deleted
public:
	SpaceInvaderEnemyBullet();
	void Initialise(Vector2D startPosition, Vector2D startVelocity);
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();	
};