//Author: w18024358
//Purpose: The purpose of this class is to ensure that the Space Invaders follow a set Formation 
#pragma once
#include "GameObject.h"

class SpaceInvaderFormation : public GameObject
{
private:
	Circle2D collisionShape;
	int direction;									//0 Left, 1 Right, 2 Left Down, 3 Right Down
	float downTimer;								//When formation moves down moves down for this amount of time
public:
	SpaceInvaderFormation();
	void Initialise();
	void Update(float frameTime);
	void Render() override;							//Overriding this so we Render nothing instead of no image
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void MoveDownLeft();							//Tells enemies when to move down on the Left
	void MoveDownRight();							//Tells enemies when to move down on the Right
};

