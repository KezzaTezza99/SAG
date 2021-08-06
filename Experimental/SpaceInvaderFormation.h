#pragma once
#include "GameObject.h"

class SpaceInvaderFormation : public GameObject
{
private:
	Circle2D collisionShape;
	int direction;				//0 Left, 1 Right, 2 Left Down, 3 Right Down
	float downTimer;
public:
	SpaceInvaderFormation();
	~SpaceInvaderFormation();
	void initialise();
	void update(float frameTime);
	void render();					//Overriding this so we render nothing instead of no image
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void MoveDownLeft();
	void MoveDownRight();
	//Need these for it to be happy -> maybe upgrade to component system
};

