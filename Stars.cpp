#include "Stars.h"

Stars::Stars()
{

}

void Stars::initialise(Vector2D startPosition)
{
	position = startPosition;
	angle = 0;
	LoadImage(L"star.bmp");
}

void Stars::update(float frameTime)
{
	
}

IShape2D& Stars::GetShape()
{
	collisionShape.PlaceAt(position, 32);
	return collisionShape;
}

void Stars::HandleCollision(GameObject& other)
{

}

