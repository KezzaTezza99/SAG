//Author: w18024358
//Purpose: To ensure that the all Space Invader Enemies move in a formation uniformally 
#include "SpaceInvaderFormation.h"

SpaceInvaderFormation::SpaceInvaderFormation()
{
	position.set(playingArea.GetTopLeft().XValue + 100, 850);
	direction = 1;									//Formation starts moving Right
	downTimer = 1.0f;								//When moving down it'll last 1 second
}

void SpaceInvaderFormation::Initialise()
{
	position.set(playingArea.GetTopLeft().XValue + 100, 850);
	direction = 1;
	downTimer = 1.0f;
}

void SpaceInvaderFormation::Update(float frameTime)
{ 
	if (direction == 2)
	{
		//Start counting down the Timer
		downTimer = downTimer - frameTime;
		position = position + Vector2D(0, -200) * frameTime;
		if (downTimer <= 0.0f)
			direction = 1;							//Move Right
	}
	if (direction == 3)
	{
		downTimer = downTimer - frameTime;
		position = position + Vector2D(0, -200) * frameTime;
		if (downTimer <= 0.0f)
			direction = 0;							//Move Left
	}
	if (direction == 1)
		position = position + Vector2D(200, 0) * frameTime;
	if (direction == 0)
		position = position + Vector2D(-200, 0) * frameTime;
}

void SpaceInvaderFormation::Render() {}

IShape2D& SpaceInvaderFormation::GetShape()
{
	return collisionShape;
}

void SpaceInvaderFormation::HandleCollision(GameObject& other) {}

void SpaceInvaderFormation::MoveDownLeft()
{
	direction = 2;
	if (downTimer <= 0)
		downTimer = 1.0f;
}

void SpaceInvaderFormation::MoveDownRight()
{
	direction = 3;
	if (downTimer <= 0)
		downTimer = 1.0f;
}