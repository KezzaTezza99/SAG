#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class SpaceInvaderLevelManager : public GameObject
{
private:
	int levelNumber;
	int numOfEnemies;
	int score;
	Circle2D collisionShape;
	ObjectManager* pObjectManager;

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
};

