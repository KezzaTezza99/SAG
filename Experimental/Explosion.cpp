#include "Explosion.h"
#include "mydrawengine.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Rock.h"
#include "Mines.h"

Explosion::Explosion()
{
    currentImage = 0.00f;
    animationSpeed = 0.00f;

    images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
    images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
    images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
    images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
    images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
    images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
    images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
    images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");
}

Explosion::~Explosion()
{
}

void Explosion::initialise(Vector2D position)
{
    this->position = position;

    images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
    images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
    images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
    images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
    images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
    images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
    images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
    images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");

    currentImage = 0.00f;
    isActive = true;
}

void Explosion::update(float frameTime)
{
    animationSpeed = 20.00f;
    currentImage += frameTime * animationSpeed;

    if (currentImage >= 8)
    {
        isActive = false;
    }
}

void Explosion::render()
{
    MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], 2.5f, angle);
}

IShape2D& Explosion::GetShape()
{
    //explosionRadius.PlaceAt(position, 140.0f);
    //collisionShape.PlaceAt(position, 200.0f);

    //return  collisionShape, explosionRadius;
    return collisionShape;
}

void Explosion::HandleCollision(GameObject& other)
{
}

void Explosion::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(explosionRadius.GetCentre(), explosionRadius.GetRadius(), MyDrawEngine::RED);
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::GREEN);
}
