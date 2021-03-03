#include "Player.h"
#include "myinputs.h"

//C before the variable name stands for Constant
const float cAcceleration = 200.0f;	
//const float cGravity = 250.0f;	
const float cFriction = 0.5f;	
const float cTurnSpeed = 1.0f; 

Player::Player()
{
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
}

void Player::initialise()
{
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	LoadImage(L"spaceship.bmp");
}

void Player::update(float frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();

	if (pInputs->KeyPressed(DIK_W))
	{
		acceleration.setBearing(angle, cAcceleration);
		velocity = velocity + acceleration * frameTime;
	}
	if (pInputs->KeyPressed(DIK_A))
	{
		angle = angle - cTurnSpeed * frameTime;
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		acceleration.setBearing(angle, cAcceleration);
		velocity = velocity - acceleration * frameTime;
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		angle = angle + cTurnSpeed * frameTime;
	}
	velocity = velocity - velocity * cFriction * frameTime;
	position = position + velocity * frameTime;
}