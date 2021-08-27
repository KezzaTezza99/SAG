//Author: w18024358
//Purpose: Providing a way for the Player to start the mini game
#include "SpaceInvadersArcadeMachine.h"
#include "SpaceInvaderLevelManager.h"
#include "ArcadePlayer.h"
#include "Shapes.h"

SpaceInvadersArcadeMachine::SpaceInvadersArcadeMachine()
{
    this->pObjectManager = pObjectManager;
    position.set(600, 500);
    startSpaceInvaders = false;
}

void SpaceInvadersArcadeMachine::Initialise(ObjectManager* pObjectManager)
{
    this->pObjectManager = pObjectManager;

    position.set(600, 500);
    startSpaceInvaders = false;
    LoadImage(L"InvaderMachine.png");
}

void SpaceInvadersArcadeMachine::Update(float frameTime)
{
    if (startSpaceInvaders)
    {
        //Creating the Space Invaders Level Manager
        SpaceInvaderLevelManager* pLevelManager = new SpaceInvaderLevelManager();
        pLevelManager->Initialise(&*pObjectManager);
        pObjectManager->AddObject(pLevelManager);
        //Delete the Space Invader Arcade Machine
        Deactivate();
    }
}

IShape2D& SpaceInvadersArcadeMachine::GetShape()
{
    collisionShape.PlaceAt(position, 200.0f);
    return collisionShape;
}

void SpaceInvadersArcadeMachine::HandleCollision(GameObject& other)
{
    if (typeid(other) == typeid(ArcadePlayer))
    {
        startSpaceInvaders = true;
    }
}

void SpaceInvadersArcadeMachine::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}