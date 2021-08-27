//Author: w18024358	
//Purpose: A level manager that is created if the Player chooses to 
//play the Asteroids Mini Game. The level manager will be responsible 
//for handelling the levels, spawning of enemies, tracking score and ending the game 
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class AsteroidsLevelManager: public GameObject
{
private:
	int levelNumber;								//Keeps track off the Level Number
	int numOfAsteroids;								//Amount of Asteroids per level
	int numOfMines;									//Number of Mines per level
	int score;										//Keeps track of Player's current score
	Vector2D randomPosition;						//Creating a random position vector for Enemy Ships to spawn at
	Circle2D collisionShape;						//Used for Collision Detection and needed until update to Component System
	ObjectManager* pObjectManager;					//Used to created Bullets etc / Needed to pass GO's to OM
	float startRound;								//Timer which counts down before the first level starts
	bool gameOver;									//Flag used to indicate when the Player has died
	bool gameWon;									//Flag used to indicate when the Player has won
public:
	AsteroidsLevelManager();
	void Initialise(ObjectManager* pObjectManager);
	void Render() override;
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();							//Used for debugging while messing with Collisions
	void StartLevel();								//Starts the level
	void EnemyDead(std::wstring typeOfEnemy);		//Used to tell Level Manager what Enemy Died, used to add different score
	void GameWon();									//Called when Player reaches 'X' round
	void GameOver();								//Called when Player dies
	void DecreaseAsteroidCount();					//Used to decrement one from the numOfAsteroids every time a "big" asteroid
													//is destroyed and when the count reaches 0 then the next level can start
													//done in a method so that the Rock can tell the Level Manager every time it
													//has been destroyed by Player, Enemy or Mine
};