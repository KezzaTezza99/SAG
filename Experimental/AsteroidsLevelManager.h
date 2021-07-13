#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "Player.h"

class AsteroidsLevelManager: public GameObject
{
private:
	int levelNumber;
	float nextRoundTimer;
	float endGameTime;
	int numOfAsteroids;
	int numOfShips; 
	int numOfMines;
	int score;
	Vector2D randomPosition;	//Creating a random position vector for Enemy Ships to Spawn
	Circle2D collisionShape;	
	ObjectManager* pObjectManager;
	
	//Need access to these variables outside off their scope when created
	Player* m_ThePlayer;
	Rock* m_pTheAsteroids;

public:
	AsteroidsLevelManager();
	~AsteroidsLevelManager();
	void startLevel();
	void render();
	void initialise(ObjectManager* pObjectManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();	//Used for debugging while messing with Collisions 
	void enemyDead();
	void playerDead();
};