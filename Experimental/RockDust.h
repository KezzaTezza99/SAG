//Author: w18024358
//Purpose: Just like the Explosion class the dust class is used to add some visual flare to the game
//when smaller rocks are destroyed they will produce a small cloud of dust that will spawn at the position of the rock
//this class will expand to have multiple purposes:
//smoke effect, small dust clouds when rocks collide with one another
#pragma once
#include "GameObject.h"

//Basically the same as an Explosion but happens when Rocks are destroyed
class RockDust: public GameObject
{
private:
	PictureIndex images[8];							//An array of smoke images used to create a dust effect
	float currentImage;								//The current image
	Circle2D collisionShape;						//Needed to compile until upgrade to component system
	float animationSpeed;							//How fast the animation will occur

public:
	RockDust();
	void Initialise(Vector2D position, float imageSize);
	void Update(float frameTime);
	void Render() override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};