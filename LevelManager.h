#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Player.h"

class LevelManager: public GameObject
{
private:
	int levelNumber;
	float spawnShip;	//Enemy Ship
	float endGameTime;
	int numAsteroids;
	int numShips; 

	Vector2D randomPosition;

	Circle2D collisionShape;
	ObjectManager* pObjectManager;
	Player* m_ThePlayer;
public:
	LevelManager();
	~LevelManager();
	void startLevel();
	void render();

	void initialise(ObjectManager* pObjectManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();

	void enemyDead();
	void playerDead();
};