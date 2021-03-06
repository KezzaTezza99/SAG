#include "Bullet.h"

Bullet::Bullet()
{
	velocity.set(0, 0);
	lifeTime = 2.0f;	//Getting rid of Warning
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
