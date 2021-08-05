#include "SpaceInvaderBullet.h"
#include "SpaceInvadeEnemy.h"
#include "SpaceInvaderPlayer.h"

SpaceInvaderBullet::SpaceInvaderBullet()
{
    velocity.set(0, 0);
    lifeTime = 3.0f;
}

SpaceInvaderBullet::~SpaceInvaderBullet()
{
}

void SpaceInvaderBullet::initialise(Vector2D startPosition, Vector2D startVelocity)
{
    position = startPosition;
    velocity = startVelocity;
    lifeTime = 3.0f;
    imageSize = 0.5f;
    LoadImage(L"plasma.bmp");
}

void SpaceInvaderBullet::update(float frameTime)
{
    position = position + velocity * frameTime;
    lifeTime = lifeTime - frameTime;

    if (lifeTime <= 0.0f)
    {
        isActive = false;
    }
}

IShape2D& SpaceInvaderBullet::GetShape()
{
    collisionShape.PlaceAt(position, 10);
    return collisionShape;
}

void SpaceInvaderBullet::HandleCollision(GameObject& other)
{
    if (typeid(other) == typeid(SpaceInvadeEnemy) || typeid(other) == typeid(SpaceInvaderPlayer))
    {
        isActive = false;
    }
}

void SpaceInvaderBullet::DrawCollision()
{
    //Shows the Collision Shape
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
    //Line Showing the Direction of Object
    MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}
