//Author: w18024358
//Purpose: The Explosion class has two purposes, the first being an explosion... when ever an explosion is needed
//such as the destruction of a mine then the class creates an explosion animation at the position
//The second purpose is to be used as a visual effect for the Hunted Player. The player can use the class
//to simulate a boost / jet effect when the Player presses L Shift
#pragma once
#include "GameObject.h"

class Explosion: public GameObject
{
private:
	PictureIndex images[8];							//Stores an array of images to display an animation of an Explosion
	Vector2D velocity;	
	Circle2D collisionShape;
	float currentImage;								//Current Image 
	float animationSpeed;							//How fast the animation will be
public:
	Explosion();
	//Explosion Default will be Image Size 2.5f, time of 20 seconds and have no movement (Explosion)
	//Otherwise the Explosion is used as a Jet (speed boost for player)
	void Initialise(Vector2D position, float size = 2.5f, float time = 20.0f, Vector2D velocity = Vector2D(0,0));
	void Update(float frameTime);
	void Render() override;							//Need to override the Render Method to Display the Explosion
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
};

