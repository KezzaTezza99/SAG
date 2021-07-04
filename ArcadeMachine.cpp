#include "ArcadeMachine.h"

/*
    MAKE OBJECT FACTORY
*/

/*
ArcadeMachine::ArcadeMachine()
{
}

ArcadeMachine::~ArcadeMachine()
{
}

void ArcadeMachine::initialise(ObjectManager* pObjectManager, LevelManager* pLevelManager)
{
    this->pObjectManager = pObjectManager;
    this->pLevelManager = pLevelManager;
    position.set(0, 0);

    LoadImage(L"rock1.bmp");
}

void ArcadeMachine::update(float frameTime)
{
    //Doesn't need to Update just yet
}

IShape2D& ArcadeMachine::GetShape()
{
    collisionShape.PlaceAt(position, 50.0f);
    return collisionShape;
}

void ArcadeMachine::HandleCollision(GameObject& other)
{
    //Do nothing yet
}

void ArcadeMachine::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}
*/