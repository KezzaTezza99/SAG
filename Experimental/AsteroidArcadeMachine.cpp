#include "AsteroidArcadeMachine.h"
#include "ArcadePlayer.h"

AsteroidArcadeMachine::AsteroidArcadeMachine()
{
    this->pObjectManager = pObjectManager;
    
    position.set(0, 0);
    startMiniGame = false;
}

AsteroidArcadeMachine::~AsteroidArcadeMachine()
{
}

void AsteroidArcadeMachine::initialise(ObjectManager* pObjectManager)
{
    this->pObjectManager = pObjectManager;
    //this->pSpaceInvaders = pSpaceInvaders;

    position.set(100, 100);
    startMiniGame = false;
    LoadImage(L"enemy.bmp");            //Change this
}

void AsteroidArcadeMachine::update(float frameTime)
{
    //Starts the Asteroids
    if (startMiniGame)
    {
        //Adding Asteroid Level Manager
        AsteroidsLevelManager* pLevelManager = new AsteroidsLevelManager();
        pLevelManager->initialise(&*pObjectManager);
        pObjectManager->addObject(pLevelManager);

        //Delete the Asteroids Arcade Machine
        Deactivate();
        //Deleting Space Invaders Arcade Machine
        //pSpaceInvaders->Deactivate();
    }
}

IShape2D& AsteroidArcadeMachine::GetShape()
{
    collisionShape.PlaceAt(position, 50.0f);
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

void AsteroidArcadeMachine::SetActivity()
{
    isActive = false;
}

void AsteroidArcadeMachine::Deactivate()
{
    isActive = false;
}


