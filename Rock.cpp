#include "Rock.h"

Rock::Rock()
{
	velocity.set(0, 0);
}

void Rock::initialise(Vector2D startPosition, Vector2D startVelocity)
{
	position = startPosition;
	velocity = startVelocity;
	LoadImage(L"rock1.bmp");
}

void Rock::update(float frameTime)
{
	position = position + velocity * frameTime;
}
