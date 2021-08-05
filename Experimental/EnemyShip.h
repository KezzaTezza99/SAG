#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "AsteroidPlayer.h"
#include "AsteroidsLevelManager.h"

class EnemyShip: public GameObject
{
private:
	Vector2D velocity;
	Vector2D acceleration;
	ObjectManager* pObjectManager;
	AsteroidPlayer* pThePlayer;
	Circle2D collisionShape;
	float shootDelay;
	float countDown;

public:
	EnemyShip();
	~EnemyShip();
	void initialise(ObjectManager* pObjectManager, AsteroidPlayer* pThePlayer, Vector2D randomStartPosition);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	Vector2D getPosition();
};

