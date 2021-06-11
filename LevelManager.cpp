#include "LevelManager.h"
#include "mydrawengine.h"
#include "EnemyShip.h"
#include "Rock.h"
#include "Stars.h"
#include "Player.h"


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

LevelManager::LevelManager()
{
	levelNumber = 1;
	spawnShip = 0.00f;	//Enemy Ship
	endGameTime = 0.00f;
	numAsteroids = 0;
	numShips = 0;

	this->pObjectManager = pObjectManager;
	m_ThePlayer = nullptr;	//Getting rid of the warning for not initilizing a member variable
}

LevelManager::~LevelManager()
{
	
}

void LevelManager::startLevel()
{
	levelNumber++;
	if (levelNumber == 1)
	{
		Player* pThePlayer = new Player();
		pThePlayer->initialise(&*pObjectManager);		//Need to pass in reference to object manager
		pObjectManager->addObject(pThePlayer);

		//Making the Ships spawn in a Random Position
		Vector2D randomPosition;
		randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 1000 + 1000.0f);

		EnemyShip* pShip = new EnemyShip();
		pShip->initialise(&*pObjectManager, &*pThePlayer, randomPosition);
		pObjectManager->addObject(pShip);

		this->m_ThePlayer = pThePlayer;		//Seems to fix the issue with the enemies always going to 0,0
											//Think I was sending a NULLPTR too the enemy somehow 
											//Also allows me to have access too the player in any function

		//Adding the Asteroids
		for (int i = 0; i < numAsteroids; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 400 - 100), float(rand() % 400 - 100));
			pRocks->initialise(&*pObjectManager,randomPosition, randomVelocity);
			pObjectManager->addObject(pRocks);
		}

		//Adding Stars
		for (int i = 0; i < 20; i++)
		{
			Stars* pStars = new Stars();

			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 1000 + 1000.0f);
			pStars->initialise(randomPosition);
			pObjectManager->addObject(pStars);
		}
	}

	if (levelNumber == 2)
	{
		//Spawn one more ship
		EnemyShip* pShip = new EnemyShip();
		pShip->initialise(&*pObjectManager, &*m_ThePlayer, randomPosition);
		pObjectManager->addObject(pShip);
	}

	if (levelNumber == 3)
	{
		//Spawn a bunch of ships
		for (int i = 0; i < numShips; i++)
		{
			EnemyShip* pShip = new EnemyShip();
			pShip->initialise(&*pObjectManager, &*m_ThePlayer, randomPosition);
			pObjectManager->addObject(pShip);
		}
	}
}

void LevelManager::render()
{
	//MyDrawEngine::GetInstance()->WriteText(20, 50, (L"RENDER TEST"), MyDrawEngine::RED);
	MyDrawEngine::GetInstance()->WriteText(20, 100, (L"Level "), MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(80, 100, levelNumber, MyDrawEngine::GREEN);
}

void LevelManager::initialise(ObjectManager* pObjectManager)
{
	levelNumber = 0;
	spawnShip = 5.00f;	//Enemy Ship
	endGameTime = 30.00f;
	numAsteroids = 10;
	numShips = 5;

	this->pObjectManager = pObjectManager;

	startLevel();
}

void LevelManager::update(float frameTime)
{
	spawnShip -= frameTime;

	if (levelNumber == 1 && spawnShip <= 0.00f)
	{
		startLevel();
		spawnShip = 5.00f;
	}

	if (levelNumber == 2 && spawnShip <= 0.00f)
	{
		startLevel();
		spawnShip = 5.00f;
	}

	if (levelNumber == 3 && spawnShip <= 0.00f)
	{
		startLevel();
		spawnShip = 5.00f;
	}
}

IShape2D& LevelManager::GetShape()
{
	return collisionShape;
}

void LevelManager::HandleCollision(GameObject& other)
{

}

void LevelManager::DrawCollision()
{

}

void LevelManager::enemyDead()
{

}

void LevelManager::playerDead()
{
	
}
