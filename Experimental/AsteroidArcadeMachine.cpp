//Author: w18024358
//Purpose: Implement the code needed for the arcade machine to work
#include "AsteroidArcadeMachine.h"
#include "ArcadePlayer.h"
#include "AsteroidsLevelManager.h"

AsteroidArcadeMachine::AsteroidArcadeMachine()
{
    this->pObjectManager = pObjectManager;
    position.set(-600, 500);
    startMiniGame = false;
}

void AsteroidArcadeMachine::Initialise(ObjectManager* pObjectManager)
{
    this->pObjectManager = pObjectManager;
    //Not using PlayingArea here becasue some reason even though the X is on the Right it keeps appearing on the Left? 
    //and vice versa so having to use extreme numbers to get it where I want.
    //tried GetTopRight / Left and it appears todo the Opposite
    position.set(-600, 500);
    startMiniGame = false;
    LoadImage(L"AsteroidMachine.png");           
}

void AsteroidArcadeMachine::Update(float frameTime)
{
    //Starts the Asteroids
    if (startMiniGame)
    {
        //Adding Asteroid Level Manager
        AsteroidsLevelManager* pLevelManager = new AsteroidsLevelManager();
        pLevelManager->Initialise(&*pObjectManager);
        pObjectManager->AddObject(pLevelManager);

        //Delete the Asteroids Arcade Machine
        Deactivate();
    }
}

IShape2D& AsteroidArcadeMachine::GetShape()
{
    collisionShape.PlaceAt(position, 200.0f);
    return collisionShape;
}

void AsteroidArcadeMachine::HandleCollision(GameObject& other)
{
    //Start Mini Game
    if (typeid(other) == typeid(ArcadePlayer))
    {
        startMiniGame = true; 
    }
}

void AsteroidArcadeMachine::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}


