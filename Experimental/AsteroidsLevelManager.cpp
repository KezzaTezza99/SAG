//Author: w18024358
//Purpose: Implement the functionallity needed for a functional level manager
#include "AsteroidsLevelManager.h"
#include "Rock.h"
#include "Stars.h"
#include "Mines.h"
#include "gamecode.h"
#include "AsteroidPlayer.h" 

//Original amount of asteroids that spawn
const int ASTEROIDS = 6;							//Used to reset the Asteroids back when new level starts       

AsteroidsLevelManager::AsteroidsLevelManager()
{
	//Starts at -1 to increment to 0 which will spawn the Player before game starts
	levelNumber = -1;
	numOfAsteroids = ASTEROIDS;						//Will always be set to 6 but levels can add more on top of original num
	numOfMines = 2;									//Number of Initial Mines that will Spawn
	score = 0;										//Used to keep track of the score
	this->pObjectManager = pObjectManager;			
	startRound = 5.0f;								//At the begining of the Game Player has 5 seconds before the start
	gameOver = false;								//Flag for when the Game is over used to display Game Over Text
	gameWon = false;								//Flag for when the Game is won
}

void AsteroidsLevelManager::Initialise(ObjectManager* pObjectManager)
{
	levelNumber = -1;
	numOfAsteroids = ASTEROIDS;
	numOfMines = 2;
	score = 0;
	this->pObjectManager = pObjectManager;
	gameOver = false;
	gameWon = false;
	startRound = 5.0f;
	StartLevel();									//Starting the Level when everything is Initilased which starts the timer
}

void AsteroidsLevelManager::Render()
{
	//Rendering specific text to user based on level number and or flags
	if (levelNumber == 0)
	{
		//Giving the User some useful information before the Game Starts
		//Displaying how long till Game starts
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200,
												playingArea.GetTopLeft().YValue - 200), 
												L"Level starting in: ", MyDrawEngine::WHITE);
		//Displaying round timer
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 180,
												playingArea.GetTopLeft().YValue - 200), (int)startRound, 
												MyDrawEngine::WHITE);
		//Rules
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 400,
												playingArea.GetCentre().YValue - 600), 
												L"Destroy all Large Asteroids to Advance", MyDrawEngine::WHITE);
		//How to Play
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200,
												playingArea.GetCentre().YValue - 700), L"WASD To Move",
												MyDrawEngine::WHITE);
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200,
												playingArea.GetCentre().YValue - 800), L"Space To Shoot",
												MyDrawEngine::WHITE);
	}
	//Display this to the User once the game starts
	else
	{
		//Playing area ensures text is always in same location for all screen types and users
		//Displaying the current level at the top left hand corner of the screen
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetTopLeft().XValue + 50, 
												playingArea.GetTopLeft().YValue - 20), (L"Level: "), MyDrawEngine::GREEN);

		//Displying the Level Number
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetTopLeft().XValue + 200,
												playingArea.GetTopLeft().YValue - 20), levelNumber, MyDrawEngine::GREEN);

		//Displaying Score at the top right hand corner of the screen
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetTopRight().XValue - 270,
												playingArea.GetTopRight().YValue - 20), (L"Score: "), MyDrawEngine::GREEN);

		//Displaying the current score value
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetTopRight().XValue - 100,
												playingArea.GetTopRight().YValue - 20), score, MyDrawEngine::GREEN);
	}
	//When the game is over this will display instead
	if (gameOver)
	{
		MyDrawEngine::GetInstance()->ClearBackBuffer();

		//Displaying text telling the user they have lost and giving them information 
		//such as score and the current level they died on
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue + 100), L"You Died!", MyDrawEngine::RED);

		//Displaying the Final Score
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue), L"Final Score: ", MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100, 
												playingArea.GetCentre().YValue), score, MyDrawEngine::RED);
		
		//Displaying the level and level number the Player reached
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue - 100), L"Current Level: ", MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 150,
												playingArea.GetCentre().YValue - 100), levelNumber, MyDrawEngine::RED);

		//Displaying text to tell user to return to Main Menu
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 460,
												playingArea.GetCentre().YValue - 200), 
												L"Please return to the Main Menu using ESC", MyDrawEngine::WHITE);
	}

	//The player has won the game
	if (gameWon)
	{
		//Displaying practically the same information as when the Player Dies
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue + 100), L"You Won!", MyDrawEngine::GREEN);

		//Displaying the Final Score
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue), L"Final Score: ", MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100,
												playingArea.GetCentre().YValue), score, MyDrawEngine::GREEN);

		//Displaying the level and level number the Player reached
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue - 100), L"Current Level: ",
												MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 150,
												playingArea.GetCentre().YValue - 100), levelNumber, MyDrawEngine::GREEN);

		//Displaying text to tell user to return to Main Menu
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 460,
												playingArea.GetCentre().YValue - 200), 
												L"Please return to the Main Menu using ESC", MyDrawEngine::WHITE);
	}
}

void AsteroidsLevelManager::Update(float frameTime)
{
	//Counting down from 5
	startRound -= frameTime;

	//Level 1 starts a differnet way than the others, it uses a timer which allows the user to move around 
	//briefly before the Level starts
	//Starts level 1
	if (levelNumber == 0 && startRound <= 0.0f)
		StartLevel();
	
	//Starts level 2
	if (levelNumber == 1 && numOfAsteroids == 0)
	{
		numOfAsteroids = ASTEROIDS + 4;
		StartLevel();
	}
	//Starts level 3
	if (levelNumber == 2 && numOfAsteroids == 0)
	{
		numOfAsteroids = ASTEROIDS + 8;
		StartLevel();
	}
	//Starts level 4
	if (levelNumber == 3 && numOfAsteroids == 0)
	{
		numOfAsteroids = ASTEROIDS;
		StartLevel();
	}
	//Starts level 5
	if (levelNumber == 4 && numOfAsteroids == 0)
	{
		numOfAsteroids = ASTEROIDS;
		StartLevel();
	}
	//If level 6 begins then the player has won
	if (levelNumber == 5 && numOfAsteroids == 0)
		GameWon();
}

IShape2D& AsteroidsLevelManager::GetShape()
{
	return collisionShape;
}

void AsteroidsLevelManager::HandleCollision(GameObject& other) {}
void AsteroidsLevelManager::DrawCollision() {}

void AsteroidsLevelManager::StartLevel()
{
	//Increments the level number every time StartLevel is called
	levelNumber++;
	
	if (levelNumber == 0)
	{
		//Creating Player here so they can move around before the wave starts
		AsteroidPlayer* pThePlayer = new AsteroidPlayer();
		//Passing in object manager to create bullets
		pThePlayer->Initialise(&*pObjectManager, this);
		pObjectManager->AddObject(pThePlayer);

		//Adding Stars
		for (int i = 0; i < 20; i++)
		{
			Stars* pStars = new Stars();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 500 + 500.0f);
			pStars->Initialise(randomPosition);
			pObjectManager->AddObject(pStars);
		}
	}

	if (levelNumber == 1)
	{
		//Adding the Asteroids
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->Initialise(&*pObjectManager, this, randomPosition, randomVelocity, imageSize);
			pObjectManager->AddObject(pRocks);
		}
	
		//Adding Mines
		for (int i = 0; i < numOfMines; i++)
		{
			Mines* pMines = new Mines();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 500 - 100), float(rand() % 500 - 100));
			pMines->Initialise(&*pObjectManager, this, randomPosition, randomVelocity);
			pObjectManager->AddObject(pMines);
		}
		//Increasing the amount for the next round
		numOfMines += 2;
	}
	//Starting the next wave
	if (levelNumber == 2)
	{
		//Creating more Asteroids
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->Initialise(&*pObjectManager, this, randomPosition, randomVelocity, imageSize);
			pObjectManager->AddObject(pRocks);
		}
		//Creating more Mines
		for (int i = 0; i < numOfMines; i++)
		{
			Mines* pMines = new Mines();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 400 - 100), float(rand() % 400 - 100));
			pMines->Initialise(&*pObjectManager, this, randomPosition, randomVelocity);
			pObjectManager->AddObject(pMines);
		}
		//Increasing the amount of Asteroids and Mines again to increase difficulty
		numOfMines += 4;
	}
	//Next Wave
	if (levelNumber == 3)
	{
		//Spawning more Asteroids
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->Initialise(&*pObjectManager, this, randomPosition, randomVelocity, imageSize);
			pObjectManager->AddObject(pRocks);
		}
		//Add Mines
		numOfMines += 8;
	}
	//Wave 4 which will be the Hardest and last level for now before player wins the game
	if (levelNumber == 4)
	{
		//Spawning more Asteroids
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->Initialise(&*pObjectManager, this, randomPosition, randomVelocity, imageSize);
			pObjectManager->AddObject(pRocks);
		}
		//Spawning Mines
		for (int i = 0; i < numOfMines; i++)
		{
			Mines* pMines = new Mines();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 400 - 100), float(rand() % 400 - 100));
			pMines->Initialise(&*pObjectManager, this, randomPosition, randomVelocity);
			pObjectManager->AddObject(pMines);
		}
	}
}

void AsteroidsLevelManager::EnemyDead(std::wstring typeOfEnemy)
{
	//Depending on the string passed as a paramater the score will increase by 'X' amount
	if (typeOfEnemy == L"Asteroid")
	{
		score += 2;
	}

	if (typeOfEnemy == L"Small Asteroid")
	{
		score += 8;
	}

	if (typeOfEnemy == L"Mine")
	{
		score += 4;
	}
}

void AsteroidsLevelManager::GameWon()
{
	//Game has won so stop the game and display the Game Won Text
	gameWon = true;
	Game::instance.StopGame();
}

void AsteroidsLevelManager::GameOver()
{
	//Game is over so stop the game and display Game Over Text
	gameOver = true;
	Game::instance.StopGame();
}

void AsteroidsLevelManager::DecreaseAsteroidCount()
{
	//An Asteroid has been destroyed either by Player, Enemy or Mine
	numOfAsteroids--;
}