//Author: w18024358
//Purpose: The purpose of the Game Object is to provide a simple way of using objects within the game 
//allows for abstraction and gives the programmer a way to interact with all Object's easily 
#pragma once
#include "mydrawengine.h"

class GameObject
{
private:
	PictureIndex image;								//The Bitmap that is loaded for the Game Object
protected:
	Vector2D position;								//The Position of the Game Object (x,y)
	float angle;									//Current angle of the Game Object
	bool isActive;									//If the Game Object is active or deactive (Alive / Dead etc)
	float imageSize;								//The size of the Image defualt 1.0f
	Rectangle2D playingArea;						//A rectangle that will take up the entire of the user screen (not visible)
													//which will be used to render text to the same position on any screen 
													//resoloution and aspect ratio
public:
	GameObject();
	~GameObject();
	void LoadImage(const wchar_t* filename);
	virtual void Render();							//Allows each derived class to replace this if needed
	virtual void Update(float frameTime) = 0;		//Pure Abstract Function - Everyone needs to provide this
	bool CheckIfActive() const;						//Check if the Object is Active or not used for deleting inactive objects
	virtual IShape2D& GetShape() = 0;				//Gets the collision shape of the object
	//Will Hangle the collisions for game objects
	virtual void HandleCollision(GameObject& other) = 0;
	virtual void DrawCollision();					//Allows user to Press "H" and see useful debug info such as Collision Shape
	virtual Vector2D GetPosition();					//Get's the Position of the Game Object
	void SetImageSize(float size);					//Set's the Image size of an image
	float GetImageSize() const;						//Get's the size of the current game object Image
	void WrapScreen();								//Allows Game Object's to wrap around the Screen if necessary
	void Deactivate();								//Set's isActive to false and allows the object to be deleted from the game
};