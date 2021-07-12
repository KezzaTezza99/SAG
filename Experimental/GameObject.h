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
	float imageSize;

public:
	GameObject();
	~GameObject();
	void LoadImage(const wchar_t* filename);
	virtual void render();	//Allows each derived class to replace this if needed
	virtual void update(float frameTime) = 0;	//Pure Abstract Function
	bool checkIfActive() const;
	virtual IShape2D& GetShape() = 0;
	virtual void HandleCollision(GameObject& other) = 0;
	virtual void DrawCollision();
	virtual Vector2D getPosition();
	void SetImageSize(float size);
	float GetImageSize() const;
	void WrapScreen();
};

