//Author: w18024358
//Purpose: Implement the necessary code to produce an explosion animation as well as 
//a boost effect for the Hunted Player
#include "Explosion.h"

Explosion::Explosion()
{
    currentImage = 0.00f;                           //Initialising to 0
    animationSpeed = 0.00f;                         //Initialising to 0
    
    //Adding the 8 Different Images into the Array
    images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
    images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
    images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
    images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
    images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
    images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
    images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
    images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");
}

void Explosion::Initialise(Vector2D position, float size, float time, Vector2D velocity)
{
    //Setting the Member Variables to be equal to the Paramaters passed
    this->position = position;
    imageSize = size;
    this->animationSpeed = time;
    this->velocity = velocity;
    
    //Resetting Images just as a Precaution
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

void Explosion::Update(float frameTime)
{
    //Adding to the current image over time multiplied by the speed of the animation
    //this makes the images go from 1-8 (0-7 0 based index)
    currentImage += frameTime * animationSpeed;

    //After the final image then Deactivate the Explosion
    if (currentImage >= 8)
    {
        Deactivate();
    }
    
    //By default Velocity is 0,0 so wont do anything / only needed for Hunted Player Jet Engine
    position = position + velocity * frameTime;
}

void Explosion::Render()
{
    //Rendering the Explosion differently than normal
    MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], imageSize, angle);
}

IShape2D& Explosion::GetShape()
{
    return collisionShape;
}

void Explosion::HandleCollision(GameObject& other) {}
void Explosion::DrawCollision() {}