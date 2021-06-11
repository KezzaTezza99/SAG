#include "Player.h"
#include "myinputs.h"
#include "Bullet.h"
#include <typeinfo>
#include "Rock.h"
#include "EnemyShip.h"
#include "Explosion.h"

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

	//This is here to stop a warning I was getting with not initilazing member variables
	this->pObjectManager = pObjectManager;
}

Player::~Player()
{

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
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue + 0.0f, -position.YValue + 0.0f));

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
		if(pBullet)
		{
			Vector2D vel;
			vel.setBearing(angle, BULLETSPEED);
			Vector2D offset;	//This will make the bullets appear in front of Player not centre
			offset.setBearing(angle, 45.0f);
			pBullet->initialise(position + offset, vel + velocity);
			if (pObjectManager)
			{
				pObjectManager->addObject(pBullet);
				shootDelay = 0.5f;	//Setting to 0.5 every time we have shot one bullet
			}
		}
	}
	//Adding a timer to count down before allowing us to shoot again
	shootDelay = shootDelay - frameTime;
}

IShape2D& Player::GetShape()
{
	collisionShape.PlaceAt(position, 30.0f);
	return collisionShape;
}

void Player::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Rock))
	{
		//Creating a Vector for the Normal
		Vector2D normal = (position - other.getPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
			velocity = velocity * 0.6f;
		}	
	}
	else if (typeid(other) == typeid(EnemyShip))
	{
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
		MyDrawEngine::GetInstance()->WriteText(position, (L"You are Dead"), MyDrawEngine::RED);
	}
}

void Player::DrawCollision()
{
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

Vector2D Player::getPosition()
{
	return position;
}

bool Player::isDead() const
{
	return isActive;
}
