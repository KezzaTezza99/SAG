#include "SpaceInvaderEnemyBullet.h"
#include "SpaceInvaderPlayer.h"

SpaceInvaderEnemyBullet::SpaceInvaderEnemyBullet()
{
    velocity.set(0, 0);
    lifeTime = 3.0f;
}

SpaceInvaderEnemyBullet::~SpaceInvaderEnemyBullet() {}

void SpaceInvaderEnemyBullet::initialise(Vector2D startPosition, Vector2D startVelocity)
{
    position = startPosition;
    velocity = startVelocity;
    lifeTime = 3.0f;
    imageSize = 2.0f;       //On my laptop the bullets are very hard to spot so made them bigger
    LoadImage(L"bullet.bmp");
}

void SpaceInvaderEnemyBullet::update(float frameTime)
{
    position = position + velocity * frameTime;
    lifeTime = lifeTime - frameTime;

    if (lifeTime <= 0.0f)
    {
        Deactivate();
    }
}

IShape2D& SpaceInvaderEnemyBullet::GetShape()
{
    collisionShape.PlaceAt(position, 10);
    return collisionShape;
}

void SpaceInvaderEnemyBullet::HandleCollision(GameObject& other)
{
    if (typeid(other) == typeid(SpaceInvaderPlayer))
        Deactivate();
}

void SpaceInvaderEnemyBullet::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
    MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}