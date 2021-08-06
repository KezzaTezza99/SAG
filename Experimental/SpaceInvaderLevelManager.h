#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class SpaceInvaderLevelManager : public GameObject
{
private:
	int levelNumber;
	int numOfEnemies;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	Vector2D offset;
	int score;
	int playerLives;
	PictureIndex playerShip;
	Vector2D lastPosition;
	//TODO DEACTIVE ASTEROID IF SPACE INVADER STARTS
public:
	SpaceInvaderLevelManager();
	~SpaceInvaderLevelManager();
	void initialise(ObjectManager* pObjectManager);
	void startLevel();
	void update(float frameTime);
	void render();
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void enemyDead();
	void playerDead();
	void GameOver();
	void Respawn();
	Vector2D GetPlayerPosition(Vector2D lastPosition);
};

