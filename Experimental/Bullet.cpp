//Author: w18024358
//Purpose: Implement all the necessary code for the bullet
#include "Bullet.h"
#include "Rock.h"
#include "EnemyShip.h"
#include "Mines.h"
#include "AsteroidPlayer.h"

Bullet::Bullet()
{
	position.set(0, 0);
	velocity.set(0, 0);
	lifeTime = 2.0f;
}

void Bullet::Initialise(Vector2D startPosition, Vector2D startVelocity)
{
	this->position = startPosition;
	this->velocity = startVelocity;
	LoadImage(L"bullet.bmp");
	lifeTime = 2.0f;
}

void Bullet::Update(float frameTime)
{
	//Asteroid Bullets will wrap the screen
	WrapScreen();
	position = position + velocity * frameTime;
	lifeTime = lifeTime - frameTime;

	if (lifeTime <= 0.0f)
	{
		Deactivate();
	}
}

IShape2D& Bullet::GetShape()
{
	collisionShape.PlaceAt(position, 4);
	return collisionShape;
}

void Bullet::DrawCollision()
{
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Bullet::HandleCollision(GameObject& other)
{
	if(typeid(other) == typeid(AsteroidPlayer) || typeid(other) == typeid(EnemyShip)
		|| typeid(other) == typeid(Mines) || typeid(other) == typeid(Rock))
	{
		Deactivate();
	}
}