#include "GameManager.h"
#include "ArcadePlayer.h"
#include "AsteroidArcadeMachine.h"
#include "SpaceInvadersArcadeMachine.h"

//Basically a Level Manager that starts the Game and will create the correct Level Manger 
//depending on the mini game selected 

GameManager::GameManager()
{
    this->pObjectManager = pObjectManager;
    this->pGameManager = pGameManager;
}

GameManager::~GameManager()
{
}

void GameManager::initialise(ObjectManager* pObjectManager, GameManager* pGameManager)
{
    this->pObjectManager = pObjectManager;
    this->pGameManager = pGameManager;
    
    //Initiliase's the Game to Arcade Mode by Creating the Mini Game's
    //Both objects need to know about each other otherwise 
    //starting one mini game leaves the other in the scene
    //player will delete the game manager also. Could stay in scene but want to do clean up
    //making player do this decouples slightly orignal version everyone could do it

    AsteroidArcadeMachine* pAsteroids = new AsteroidArcadeMachine();
    //Initialising and Adding the Asteroids Mini Game here so I can pass in SpaceInvaders alsp
    pAsteroids->initialise(&*pObjectManager);
    pObjectManager->addObject(pAsteroids);

    SpaceInvadersArcadeMachine* pSpaceInvaders = new SpaceInvadersArcadeMachine();
    pSpaceInvaders->initialise(&*pObjectManager, &*pAsteroids);
    pObjectManager->addObject(pSpaceInvaders);

  
    //Initiliase the Arcade Player
    ArcadePlayer* pArcadePlayer = new ArcadePlayer();
    pArcadePlayer->initialise(&*pGameManager);          //Needs to delete the Game Manager
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

void GameManager::Deactivate()
{
    isActive = false;
}