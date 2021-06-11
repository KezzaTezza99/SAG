#include "Bullet.h"
#include "Rock.h"
#include "EnemyShip.h"

Bullet::Bullet()
{
	velocity.set(0, 0);
	lifeTime = 2.0f;	//Getting rid of Warning
}

Bullet::~Bullet()
{

}

void Bullet::initialise(Vector2D startPosition, Vector2D startVelocity)
{
	position = startPosition;
	velocity = startVelocity;
	LoadImage(L"bullet.bmp");
	lifeTime = 2.0f;
}

void Bullet::update(float frameTime)
{
	position = position + velocity * frameTime;
	lifeTime = lifeTime - frameTime;

	if (lifeTime <= 0.0f)
	{
		isActive = false;
	}
}

IShape2D& Bullet::GetShape()
{
	collisionShape.PlaceAt(position, 6);
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
	if (typeid(other) == typeid(Rock))
	{
		isActive = false;
	}

	if (typeid(other) == typeid(EnemyShip))
	{
		isActive = false;
	}
}
