#include "Spaceship.h"
#include "myinputs.h"

//C before the variable name stands for Constant
const float cAcceleration = 1.0f;	
//const float cGravity = 250.0f;	
const float cFriction = -0.5f;	
const float cTurnSpeed = 0.2f; 

Spaceship::Spaceship()
{
	image = -1;
	angle = 0;
	position.set(0, 0);

}

void Spaceship::initialise()
{
	image = MyDrawEngine::GetInstance()->LoadPicture(L"spaceship.bmp");
}

void Spaceship::render()
{
	MyDrawEngine::GetInstance()->DrawAt(position, image, 1.0f, angle);
}

void Spaceship::update()
{
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();

	if (pInputs->KeyPressed(DIK_W))
	{
		acceleration.setBearing(angle, cAcceleration);
		velocity = velocity + acceleration;
	}
	if (pInputs->KeyPressed(DIK_A))
	{
		friction = cFriction * velocity;
		velocity = velocity + friction;
		angle = angle - cTurnSpeed;
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		acceleration.setBearing(angle, cAcceleration);
		velocity = velocity - acceleration;
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		friction = cFriction * velocity;
		velocity = velocity + friction;
		angle = angle + cTurnSpeed;
	}
	position = position + velocity;
}

//Vekicuty is a vector that measures how much a position changes in a second
//Accleration is another vector that measures how much Velocity changes in a Second 