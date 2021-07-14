#include "AsteroidsLevelManager.h"
#include "mydrawengine.h"
#include "EnemyShip.h"
#include "Rock.h"
#include "Stars.h"
#include "AsteroidPlayer.h"
#include "Mines.h"
#include "AsteroidArcadeMachine.h"

/*
		//THIS CREATES A PATTERN SUCH AS A WALL
		for(int x = 0; x < 5; x++)
			for (int y = 0; y < 5; y++)
			{
				float spacing = 200.00f;

				Stars* pTheStar = new Stars();
				Vector2D pos;
				pos.set(float(x) * spacing, float(y) * spacing);
				pTheStar->initialise(pos);
				pObjectManager->addObject(pTheStar);
			}
*/

AsteroidsLevelManager::AsteroidsLevelManager()
{
	levelNumber = 1;
	nextRoundTimer = 30.00f;
	endGameTime = 60.00f;
	numOfAsteroids = 10;
	numOfShips = 0;
	numOfMines = 2;
	score = 0;

	this->pObjectManager = pObjectManager;

	//Getting rid of the warning for not initilizing a member variable
	m_ThePlayer = nullptr;	
	m_pTheAsteroids = nullptr;
}

AsteroidsLevelManager::~AsteroidsLevelManager()
{
}

void AsteroidsLevelManager::startLevel()
{
	//----------------------------------------------------------------------------------------------
	//Start Asteroids
	levelNumber++;
	if (levelNumber == 1)
	{
		////Making the Ships spawn in a Random Position
		//Vector2D randomPosition;
		//randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 1000 + 1000.0f);
		//EnemyShip* pShip = new EnemyShip();
		//pShip->initialise(&*pObjectManager, &*pThePlayer, randomPosition);
		//pObjectManager->addObject(pShip);

		//this->m_ThePlayer = pThePlayer;		//Seems to fix the issue with the enemies always going to 0,0
												//Think I was sending a NULLPTR too the enemy somehow 
												//Also allows me to have access too the AsteroidPlayer in any function

		////Adding the Asteroids
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->initialise(&*pObjectManager, randomPosition, randomVelocity, imageSize);
			pObjectManager->addObject(pRocks);

			//Using a member variable to access in other functions if necessary
			this->m_pTheAsteroids = pRocks;
		}

		//Creating the Asteroids first as the AsteroidPlayer needs to know about them
		//Help with different collisions based on the rock size
		AsteroidPlayer* pThePlayer = new AsteroidPlayer();
		//Passing in object manager to create bullets
		pThePlayer->initialise(&*pObjectManager, &*m_pTheAsteroids);
		pObjectManager->addObject(pThePlayer);

		this->m_ThePlayer = pThePlayer;

		//Adding Stars
		for (int i = 0; i < 20; i++)
		{
			Stars* pStars = new Stars();
			Vector2D randomPosition;
			//randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 1000 + 1000.0f);
			randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 500 + 500.0f);
			pStars->initialise(randomPosition);
			pObjectManager->addObject(pStars);
		}

		for (int i = 0; i < numOfMines; i++)
		{
			Mines* pMines = new Mines();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 500 - 100), float(rand() % 500 - 100));
			pMines->initialise(&*pObjectManager, randomPosition, randomVelocity);
			pObjectManager->addObject(pMines);
		}
		numOfMines += 2;
		numOfAsteroids += 4;
	}

	if (levelNumber == 2)
	{
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->initialise(&*pObjectManager, randomPosition, randomVelocity, imageSize);
			pObjectManager->addObject(pRocks);
		}

		for (int i = 0; i < numOfMines; i++)
		{
			Mines* pMines = new Mines();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 400 - 100), float(rand() % 400 - 100));
			pMines->initialise(&*pObjectManager, randomPosition, randomVelocity);
			pObjectManager->addObject(pMines);
		}
		numOfMines += 4;
		numOfAsteroids += 8;
	}

	if (levelNumber == 3)
	{
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->initialise(&*pObjectManager, randomPosition, randomVelocity, imageSize);
			pObjectManager->addObject(pRocks);
		}

		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->initialise(&*pObjectManager, randomPosition, randomVelocity, imageSize);
			pObjectManager->addObject(pRocks);
		}
		numOfMines += 8;
	}

	if (levelNumber == 4)
	{
		for (int i = 0; i < numOfAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->initialise(&*pObjectManager, randomPosition, randomVelocity, imageSize);
			pObjectManager->addObject(pRocks);
		}

		for (int i = 0; i < numOfMines; i++)
		{
			Mines* pMines = new Mines();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 400 - 100), float(rand() % 400 - 100));
			pMines->initialise(&*pObjectManager, randomPosition, randomVelocity);
			pObjectManager->addObject(pMines);
		}
	}
	
	//This will be the End of the Mini Game
	if (levelNumber == 5)
	{
		//GameWin();
	}
}

void AsteroidsLevelManager::render()
{
	//MyDrawEngine::GetInstance()->WriteText(20, 50, (L"RENDER TEST"), MyDrawEngine::RED);
	MyDrawEngine::GetInstance()->WriteText(20, 100, (L"Level "), MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(80, 100, levelNumber, MyDrawEngine::GREEN);
}

void AsteroidsLevelManager::initialise(ObjectManager* pObjectManager)
{
	levelNumber = 0;
	nextRoundTimer = 60.00f;	//Enemy Ship
	endGameTime = 30.00f;
	numOfAsteroids = 2;
	numOfShips = 1;
	numOfMines = 2;

	this->pObjectManager = pObjectManager;
	startLevel();
}

void AsteroidsLevelManager::update(float frameTime)
{
	nextRoundTimer -= frameTime;

	if (levelNumber == 1 && nextRoundTimer <= 0.00f)
	{
		startLevel();
		nextRoundTimer = 5.00f;
	}

	if (levelNumber == 2 && nextRoundTimer <= 0.00f)
	{
		startLevel();
		nextRoundTimer = 5.00f;
	}

	if (levelNumber == 3 && nextRoundTimer <= 0.00f)
	{
		startLevel();
		nextRoundTimer = 5.00f;
	}
}

IShape2D& AsteroidsLevelManager::GetShape()
{
	return collisionShape;
}

void AsteroidsLevelManager::HandleCollision(GameObject& other)
{

}

void AsteroidsLevelManager::DrawCollision()
{

}

void AsteroidsLevelManager::enemyDead()
{
	score++;
}

void AsteroidsLevelManager::playerDead()
{
	
}
