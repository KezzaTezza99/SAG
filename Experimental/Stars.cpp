//Author: w18024358
//Purpose: To provide visual effects to the game to make it feel like space as well as 
//providing visual ques to the player in the HUnted game mode that they are moving around the terrain
#include "Stars.h"

void Stars::Initialise(Vector2D startPosition)
{
	position = startPosition;
	angle = 0;
	LoadImage(L"star.bmp");
}

void Stars::Update(float frameTime) {}
IShape2D& Stars::GetShape() { return collisionShape; }
void Stars::HandleCollision(GameObject& other) {}