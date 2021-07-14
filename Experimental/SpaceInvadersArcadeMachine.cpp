#include "SpaceInvadersArcadeMachine.h"
#include "SpaceInvaderLevelManager.h"
#include "ArcadePlayer.h"

SpaceInvadersArcadeMachine::SpaceInvadersArcadeMachine()
{
    this->pObjectManager = pObjectManager;
    this->pAsteroids = pAsteroids;

    position.set(0, 0);
    startSpaceInvaders = false;
}

SpaceInvadersArcadeMachine::~SpaceInvadersArcadeMachine()
{
}

void SpaceInvadersArcadeMachine::initialise(ObjectManager* pObjectManager, AsteroidArcadeMachine* pAsteroids)
{
    this->pObjectManager = pObjectManager;
    this->pAsteroids = pAsteroids;

    position.set(300, 300);
    startSpaceInvaders = false;
    LoadImage(L"enemy.bmp");            //Change this
}

void SpaceInvadersArcadeMachine::update(float frameTime)
{
    if (startSpaceInvaders)
    {
        //Creating the Space Invaders Level Manager
        SpaceInvaderLevelManager* pLevelManager = new SpaceInvaderLevelManager();
        pLevelManager->initialise(&*pObjectManager);
        pObjectManager->addObject(pLevelManager);

        //Delete the Space Invader Arcade Machine
        Deactivate();
        //Delete the Asteroids Arcade Machine
        pAsteroids->Deactivate();
    }
}

IShape2D& SpaceInvadersArcadeMachine::GetShape()
{
    collisionShape.PlaceAt(position, 50.0f);
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

void SpaceInvadersArcadeMachine::Deactivate()
{
    isActive = false;
}
