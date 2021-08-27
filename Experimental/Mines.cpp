//Author: w18024358
//Purpose: Implement code to allow for mines to randomly spawn and move around the scene, if shot or collided with
//they cause an explosion
#include "Mines.h"
#include "Rock.h"
#include "Bullet.h"
#include "AsteroidPlayer.h"
#include "Explosion.h"

Mines::Mines()
{
    velocity.set(0, 0);
    this->pObjectManager = pObjectManager;
    this->pLevelManager = pLevelManager;
}

void Mines::Initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager, Vector2D startPosition, Vector2D startVelocity)
{
    position = startPosition;
    velocity = startVelocity;
    this->pObjectManager = pObjectManager;
    this->pLevelManager = pLevelManager;
    LoadImage(L"mine1.bmp");
}

void Mines::Update(float frameTime)
{
    const float cTurnSpeed = 1.0f;
    WrapScreen();                                   //Mines will wrap the screen
    angle = angle - cTurnSpeed * frameTime;	        //Making the mines "spin"
    position = position + velocity * frameTime;     //Moving the mines
}

IShape2D& Mines::GetShape()
{
    collisionShape.PlaceAt(position, 60);
    return  collisionShape;
}

void Mines::HandleCollision(GameObject& other)
{
    if (typeid(other) == typeid(AsteroidPlayer) || typeid(other) == typeid(Rock)
        || typeid(other) == typeid(Mines))
    {
        //Deactivate mine
        Deactivate();
        //Create Explosion
        Explosion* pExplosion = new Explosion();
        pExplosion->Initialise(position);
        pObjectManager->AddObject(pExplosion);
    }

    if (typeid(other) == typeid(Bullet))
    {
        //Deactivate
        Deactivate();
        //Cause Explosion
        Explosion* pExplosion = new Explosion();
        pExplosion->Initialise(position);
        pObjectManager->AddObject(pExplosion);
        //Tell Level Manager Mine was destroyed to increase score
        pLevelManager->EnemyDead(L"Mine");
    }
}

void Mines::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
    MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}