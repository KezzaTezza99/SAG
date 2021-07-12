#include "RockDust.h"
#include "mydrawengine.h"

RockDust::RockDust()
{
    currentImage = 0.00f;
    animationSpeed = 0.00f;

    //Getting rid of the warning
    images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke1.bmp");
    images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke2.bmp");
    images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke3.bmp");
    images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke4.bmp");
    images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke5.bmp");
    images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke6.bmp");
    images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke7.bmp");
    images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke8.bmp");
}

RockDust::~RockDust()
{

}

void RockDust::initialise(Vector2D position)
{
    this->position = position;

    images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke1.bmp");
    images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke2.bmp");
    images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke3.bmp");
    images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke4.bmp");
    images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke5.bmp");
    images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke6.bmp");
    images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke7.bmp");
    images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"smoke8.bmp");

    currentImage = 0.00f;
    isActive = true;
}

void RockDust::update(float frameTime)
{
    animationSpeed = 50.00f;

    currentImage += frameTime * animationSpeed;

    if (currentImage >= 8)
    {
        isActive = false;
    }
}

void RockDust::render()
{
    //1.5 size 
    //1 good size for small rocks maybe update this to change
	MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], 1.5f, angle);
}

IShape2D& RockDust::GetShape()
{
	return collisionShape;
}

void RockDust::HandleCollision(GameObject& other)
{
	//Dont need collision
}
