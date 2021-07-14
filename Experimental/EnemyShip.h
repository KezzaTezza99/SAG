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
	Vector2D playerPos;
	//Vector2D playerPosition;
	Vector2D currentPosition;
	//Want the Ship to create bullets to shoot AsteroidPlayer
	ObjectManager* pObjectManager;
	float shootDelay;
	Circle2D collisionShape;
	AsteroidPlayer* pThePlayer;
	float playerAngle;
	float wait;

public:
	EnemyShip();
	~EnemyShip();
	void initialise(ObjectManager* pObjectManager, AsteroidPlayer* pThePlayer, Vector2D randomStartPosition);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	Vector2D getPosition();
	void getPlayerPosition();
	void getPlayer();
};

