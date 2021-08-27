//Author: w18024358
//Purpose: Implement code that can allow for a general level manager that creates all the necessary entities to 
//allow the player to interact with any mini game necessary
#include "GameManager.h"
#include "ArcadePlayer.h"
#include "AsteroidArcadeMachine.h"
#include "SpaceInvadersArcadeMachine.h"
#include "HuntedArcadeMachine.h"

//Basically a Level Manager that starts the Game and will create the correct Level Manger 
//depending on the mini game selected 
//purpose was to make the "arcade" section achieve the animation task and the mini games achieve
//level managers and component system but with other things happening over the Holidays this was to ambitious
//arcade level was going to look like an arcade with a player and animations
GameManager::GameManager()
{
    this->pObjectManager = pObjectManager;
}

void GameManager::Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles)
{
    //As the Game Manager has a reference to the Particle System I can now pass it to all the "Arcade Machines"
    //who can then pass it to their respected Level Managers if they will utilize the Particle System
    //so far only Hunted Player will use Particles but can easily add to others using this method
    this->pObjectManager = pObjectManager;

    //Initiliase's the Game to Arcade Mode by Creating the Mini Game's
    //Creating Asteroid Arcade Machine
    AsteroidArcadeMachine* pAsteroids = new AsteroidArcadeMachine();
    pAsteroids->Initialise(pObjectManager);
    pObjectManager->AddObject(pAsteroids);
    
    //Creating Space Invaders Arcade Machine
    SpaceInvadersArcadeMachine* pSpaceInvaders = new SpaceInvadersArcadeMachine();
    pSpaceInvaders->Initialise(pObjectManager);
    pObjectManager->AddObject(pSpaceInvaders);

    //Creating "Hunted" Arcade Machine
    HuntedArcadeMachine* pHunted = new HuntedArcadeMachine();
    pHunted->Initialise(pObjectManager, pParticles);
    pObjectManager->AddObject(pHunted);

    //Initiliase the Arcade Player
    ArcadePlayer* pArcadePlayer = new ArcadePlayer();
    //Player is responsible for deleting the Game Manager and the Mini Games
    pArcadePlayer->Initialise(this, &*pAsteroids, &*pSpaceInvaders, pHunted);
    pObjectManager->AddObject(pArcadePlayer);
}
void GameManager::Update(float frameTime) {}        //No need to Update

void GameManager::Render()
{
    //As still work in progress displaying message
    MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200, 
                                            playingArea.GetCentre().YValue - 550), L"Still work in Progress", 
                                            MyDrawEngine::WHITE, 1);
    //Controls and Rules
    MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200, 
                                            playingArea.GetCentre().YValue - 650), L"WASD to move", MyDrawEngine::WHITE, 1);
    MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200, 
                                            playingArea.GetCentre().YValue - 750), 
                                            L"Interact with Machine to start Mini Game", MyDrawEngine::WHITE, 1);
}

IShape2D& GameManager::GetShape()
{
    return collisionShape;                          //Needed until Component or Pick and Mix implemented
}

void GameManager::HandleCollision(GameObject& other) {}