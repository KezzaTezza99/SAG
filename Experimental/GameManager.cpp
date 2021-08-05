#include "GameManager.h"
#include "ArcadePlayer.h"
#include "AsteroidArcadeMachine.h"
#include "SpaceInvadersArcadeMachine.h"

//Basically a Level Manager that starts the Game and will create the correct Level Manger 
//depending on the mini game selected 

GameManager::GameManager()
{
    this->pObjectManager = pObjectManager;
}

GameManager::~GameManager() {}

void GameManager::initialise(ObjectManager* pObjectManager)
{
    this->pObjectManager = pObjectManager;
    
    //Initiliase's the Game to Arcade Mode by Creating the Mini Game's
    AsteroidArcadeMachine* pAsteroids = new AsteroidArcadeMachine();
    pAsteroids->initialise(&*pObjectManager);
    pObjectManager->addObject(pAsteroids);

    SpaceInvadersArcadeMachine* pSpaceInvaders = new SpaceInvadersArcadeMachine();
    pSpaceInvaders->initialise(&*pObjectManager);
    pObjectManager->addObject(pSpaceInvaders);

    //Initiliase the Arcade Player
    ArcadePlayer* pArcadePlayer = new ArcadePlayer();
    //Player is responsible for deleting the Game Manager and the Mini Games
    pArcadePlayer->initialise(this, &*pAsteroids, &*pSpaceInvaders);
    pObjectManager->addObject(pArcadePlayer);
}

void GameManager::render()
{
    MyDrawEngine::GetInstance()->WriteText(20, 500, (L"Game Manager"), MyDrawEngine::GREEN);
}

void GameManager::update(float frameTime)
{

}

IShape2D& GameManager::GetShape()
{
    return collisionShape;
}

void GameManager::HandleCollision(GameObject& other)
{
}
