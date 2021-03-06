#include "Player.h"
#include "myinputs.h"
#include "Bullet.h"

const float cAcceleration = 200.0f;	
//const float cGravity = 250.0f;	
const float cFriction = 0.5f;	
const float cTurnSpeed = 1.0f; 
const float BULLETSPEED = 400.0f;

Player::Player()
{
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	shootDelay = 0;

	this->pObjectManager = pObjectManager;	//This is here to stop a warning i was getting with not initilazing member variables
}

void Player::initialise(ObjectManager* pObjectManager)
{
	//Repeating basically the same as Constructor just making sure Everything is set 
	//On the chance that the Constructor Fails all values will be set here anyway
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	LoadImage(L"spaceship.bmp");

	this->pObjectManager = pObjectManager;
	shootDelay = 0;
}

void Player::update(float frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();

	//Movement
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

	//Shooting
	if (pInputs->KeyPressed(DIK_SPACE) && shootDelay <= 0)	//Only allowed to shoot when shoot delay is 0
	{
		Bullet* pBullet = new Bullet();
		Vector2D vel;	
		vel.setBearing(angle, BULLETSPEED);	
		Vector2D offset;	//This will make the bullets appear in front of Player not centre
		offset.setBearing(angle, 45.0f);
		pBullet->initialise(position + offset, vel + velocity);

		if(pObjectManager)
		{
			pObjectManager->addObject(pBullet);
			shootDelay = 0.5f;	//Setting to 0.5 every time we have shot one bullet
		}
	}
	//Adding a timer to count down before allowing us to shoot again
	shootDelay = shootDelay - frameTime;
}