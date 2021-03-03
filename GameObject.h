#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"

class GameObject
{
private:
	PictureIndex image;

protected:
	Vector2D position;
	float angle;
	bool isActive;

public:
	GameObject();
	void LoadImage(const wchar_t* filename);
	virtual void render();	//Allows each derived class to replace this if needed
	virtual void update(float frameTime) = 0;	//Pure Abstract Function
};

