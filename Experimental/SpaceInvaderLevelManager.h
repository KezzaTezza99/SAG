//Author: w18024358
//Purpose: The purpose of this level manager is the same as other Level Managers 
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class SpaceInvaderLevelManager : public GameObject
{
private:
	int levelNumber;								//Current Level Number
	int numOfEnemies;								//Number of Enemies in the formation
	Circle2D collisionShape;						//Needed until component system upgrade
	ObjectManager* pObjectManager;					//Needed to create the other Entities 
	int score;										//Used to track score
	int playerLives;								//Used to track Player's lives
	PictureIndex playerShip;						//Picture of the Player Ship that will be used as UI for Lives
	Vector2D lastPosition;							//Used to remember where Player was before they Died
	Vector2D offset;								//Offset that will keep the enemies spaced out and utilized by Formation
	int spacing;									//How much the Enemies will be spaced out on the X,Y
	int xPos;										//What does this do again
	bool gameWon;									//Flag used for displaying Game Won Text when player has won the game
	bool invadersWon;								//If the Invaders reach the bottom of the screen this flag will turn to 
													//true and the game will end, text will be displayed
	bool gameStartText;								//Used to display some starting information to Player once game starts set to false
	float gameStartTimer;							//Used to count down 5 second's then sets Flag to false to start game
public:
	SpaceInvaderLevelManager();
	void Initialise(ObjectManager* pObjectManager);
	void StartLevel();								//Called to start each level and spawn new Enemies
	void Update(float frameTime);					
	void Render() override;							//Overriding to display some text information on screen
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void EnemyDead();								//When an Enemy Ship dies it call's this method
	void PlayerDead();								//When Player dies this method is called
	void GameOver();								//When the invaders reach the bottom of the screen this method is called
	void Respawn();									//This respawns the Enemies at the start of the new round
	void GetPlayerPosition(Vector2D lastPos);		//Used to get Player Position when they died to place new player in same location
};

