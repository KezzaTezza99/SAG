#include "GameManager.h"
#include "ArcadeMachine.h"
#include "ArcadePlayer.h"

//Basically a Level Manager that starts the Game and will create the correct Level Manger 
//depending on the mini game selected 

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
}

void GameManager::initialise(ObjectManager* pObjectManager)
{
    this->pObjectManager = pObjectManager;

    //Initiliase's the Game to Arcade Mode
    ArcadeMachine* pArcade = new ArcadeMachine();
    pArcade->initialise(&*pObjectManager);
    pObjectManager->addObject(pArcade);

    //Initiliase the Arcade Player
    //ArcadePlayer* pArcadePlayer = new ArcadePlayer();
    //pArcadePlayer->initialise();
    //pObjectManager->addObject(pArcadePlayer);
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

void GameManager::Deactivate()
{
    isActive = false;
}
