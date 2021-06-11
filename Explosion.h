#pragma once
#include "GameObject.h"

class Explosion: public GameObject
{
private:
	PictureIndex images[8];
	float currentImage;
	Circle2D collisionShape;
	float animationSpeed;

public:
	Explosion();
	~Explosion();
	void initialise(Vector2D position);
	void update(float frameTime);
	void render() override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

