#include "ArcadeMachine.h"
#include "ArcadePlayer.h"

ArcadeMachine::ArcadeMachine()
{
    position.set(0, 0);
    this->pObjectManager = pObjectManager;
}

ArcadeMachine::~ArcadeMachine()
{
}

void ArcadeMachine::initialise(ObjectManager* pObjectManager)
{
    this->pObjectManager = pObjectManager;
    
    position.set(100, 100);
    startMiniGame = false;
    LoadImage(L"enemy.bmp");            //Change this
}

void ArcadeMachine::update(float frameTime)
{
    //Starts the Mini Game
    if (startMiniGame)
    {
        //Adding Asteroid Level Manager
        AsteroidsLevelManager* pLevelManager = new AsteroidsLevelManager();
        pLevelManager->initialise(&*pObjectManager);
        pObjectManager->addObject(pLevelManager);
     
        //Delete the Arcade Machine to Stop Memory Leaks
        Deactivate();
    }
    else
    {
        MyDrawEngine::GetInstance()->WriteText(Vector2D(0, 0), L"ARCADE", MyDrawEngine::RED);
    }
}

IShape2D& ArcadeMachine::GetShape()
{
    collisionShape.PlaceAt(position, 50.0f);
    return collisionShape;
}

void ArcadeMachine::HandleCollision(GameObject& other)
{
    //Start Mini Game
    if (typeid(other) == typeid(ArcadePlayer))
    {
        startMiniGame = true;
    }
}

void ArcadeMachine::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}

void ArcadeMachine::SetActivity()
{
    isActive = false;
}

void ArcadeMachine::Deactivate()
{
    isActive = false;
}


