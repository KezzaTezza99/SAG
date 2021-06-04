#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "ObjectManager.h"

class Player: public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;

	//This gives poiner to ObjectManager and allows us to create Bullets etc 
	ObjectManager* pObjectManager;

	float shootDelay;	//Allows us to shoot one bullet every time - every 0.5 seconds
	Circle2D collisionShape;

public:
	Player();
	~Player();
	void initialise(ObjectManager* pObjectManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	Vector2D getPosition();

	bool isDead() const;
};


