#include "SpaceInvaderLevelManager.h"
#include "AsteroidPlayer.h"

SpaceInvaderLevelManager::SpaceInvaderLevelManager()
{
	levelNumber = 0;
	numOfEnemies = 10;
	score = 0;
	this->pObjectManager = pObjectManager;
}

SpaceInvaderLevelManager::~SpaceInvaderLevelManager()
{
}

void SpaceInvaderLevelManager::initialise(ObjectManager* pObjectManager)
{
	levelNumber = 0;
	numOfEnemies = 10;
	score = 0;
	this->pObjectManager = pObjectManager;
	startLevel();
}

void SpaceInvaderLevelManager::startLevel()
{
	levelNumber++;
	
	if (levelNumber == 1)
	{
		AsteroidPlayer* pPlayer = new AsteroidPlayer();
		pPlayer->initialise(&*pObjectManager);
		pObjectManager->addObject(pPlayer);
	}
}

void SpaceInvaderLevelManager::update(float frameTime)
{
	if (levelNumber == 1)
	{
		startLevel();
	}
}

void SpaceInvaderLevelManager::render()
{
    MyDrawEngine::GetInstance()->WriteText(20, 100, (L"Level "), MyDrawEngine::GREEN);
    MyDrawEngine::GetInstance()->WriteInt(80, 100, levelNumber, MyDrawEngine::GREEN);
}

IShape2D& SpaceInvaderLevelManager::GetShape()
{
	return collisionShape;
}

void SpaceInvaderLevelManager::HandleCollision(GameObject& other)
{
}

void SpaceInvaderLevelManager::DrawCollision()
{
}

void SpaceInvaderLevelManager::enemyDead()
{
}

void SpaceInvaderLevelManager::playerDead()
{
}