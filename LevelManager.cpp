#include "LevelManager.h"
#include "mydrawengine.h"
#include "EnemyShip.h"
#include "Rock.h"
#include "Stars.h"
#include "Player.h"

/*
	TODO REMOVE THE MEMBER VARIABLE FOR PLAYER 
	ALSO PUT ENEMY WITH PLAYER AND IT WORKS PROPERLY 
	DO MORE TESTING 
	EXPERIMENT WITH MEMBER VARIABLE FIRST ACTUALLY COULD MAKE IT WORK?

	//Get Plasters tomorrow 
	//Get drinks
	//Get cordial and water for hotel
	//Crisps / little snacks

*/
LevelManager::LevelManager()
{
	levelNumber = 1;
	spawnShip = 5.00f;	//Enemy Ship
	endGameTime = 30.00f;
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

		this->m_ThePlayer = pThePlayer;


		//Adding the Asteroids
		for (int i = 0; i < 10; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
			Vector2D randomVelocity(float(rand() % 400 - 100), float(rand() % 400 - 100));
			pRocks->initialise(randomPosition, randomVelocity);
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
		for (int i = 0; i < 5; i++)
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
	numAsteroids = 0;
	numShips = 0;

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
