#include "Mines.h"
#include "Rock.h"
#include "Bullet.h"
#include "AsteroidPlayer.h"
#include "Explosion.h"

const float cTurnSpeed = 1.0f;

Mines::Mines()
{
    velocity.set(0, 0);
    this->pObjectManager = pObjectManager;
}

Mines::~Mines()
{
}

void Mines::initialise(ObjectManager* pObjectManager, Vector2D startPosition, Vector2D startVelocity)
{
    position = startPosition;
    velocity = startVelocity;
    this->pObjectManager = pObjectManager;
    LoadImage(L"mine1.bmp");
}

void Mines::update(float frameTime)
{
    WrapScreen();
    angle = angle - cTurnSpeed * frameTime;	
    position = position + velocity * frameTime;
}

IShape2D& Mines::GetShape()
{
    collisionShape.PlaceAt(position, 60);
    return  collisionShape;
}

void Mines::HandleCollision(GameObject& other)
{
    if (typeid(other) == typeid(AsteroidPlayer) || typeid(other) == typeid(Rock) 
        || typeid(other) == typeid(Bullet) || typeid(other) == typeid(Mines))
    {
        isActive = false;
        Explosion* pExplosion = new Explosion();
        pExplosion->initialise(position);
        pObjectManager->addObject(pExplosion);
    }
}

void Mines::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
    MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

Vector2D Mines::getPosition()
{
    return position;
}
