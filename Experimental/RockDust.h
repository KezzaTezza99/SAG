#pragma once
#include "GameObject.h"

//Basically the same as an Explosion but happens when Rocks are destroyed
class RockDust: public GameObject
{
private:
	PictureIndex images[8];
	float currentImage;
	Circle2D collisionShape;
	float animationSpeed;

public:
	RockDust();
	~RockDust();
	void initialise(Vector2D position, float imageSize);
	void update(float frameTime);
	void render() override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

