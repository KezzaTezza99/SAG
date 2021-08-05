#pragma once
#include "GameObject.h"

class SpaceInvaderBullet : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	float lifeTime;
public:
	SpaceInvaderBullet();
	~SpaceInvaderBullet();
	void initialise(Vector2D startPosition, Vector2D startVelocity);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

