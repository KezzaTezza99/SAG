//Author: w18024358
//Purpose: The Hunted Level Manager has a few purpose such as providing information from and to all Entities in this
//specific Mini Game which allows the Enemy Ship for example to always know where the Player is 
//which allows for some basic "AI" in game where the ship will "hunt" / follow the Player
//The level manager will also track information such as if an enemy has died to spawn a new enemy
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "ParticleSystem.h"
#include "HuntedPlayer.h"

class HuntedLevelManager : public GameObject
{
private:
	ObjectManager* pObjectManager;
	ParticleSystem* pParticles;
	HuntedPlayer* pThePlayer;
	Circle2D collisonShape;
	float startingTextTimer;							//Used to display info to Player during beginning of Game
	float timeAlive;									//Used instead of a Score
	bool playerDead;									//Used as a flag that will load the final screen in Render
	bool startGame;										//Flag used to stop the text timer and start the time alive timer
	bool startingText;									//Flag used to Show / Hide Text
	//Can't use playingArea to display text due to the Player being able to move off screen
	Vector2D playerPos;									//Instead using the Player's Position to Place relative to Player
	float x;											//X coord for Player pos
	float y;											//Y coord for Player pos
														//X,Y allow me to place text further along e.g. Text: Score (Int)
public:
	HuntedLevelManager();
	void Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles);
	void Render() override;									//Used to Render the Text
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void StartLevel();								//Used for creating the 1st Enemy and other random Entities
	void EnemyDead();								//When Enemy dies the level manager needs to know to create a new one
	void PlayerDead();								//Due to Circular Dependencies? Player cannot actually call this class right now
													//was supposed to use this to display the final score and some text
};