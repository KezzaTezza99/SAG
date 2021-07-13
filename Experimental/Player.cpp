#include "Player.h"
#include "myinputs.h"
#include "Bullet.h"
#include <typeinfo>
#include "Rock.h"
#include "EnemyShip.h"
#include "Explosion.h"
#include "Mines.h"
#include "ArcadeMachine.h"

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
	RockImageSize = 0.0f;
	//This is here to stop a warning I was getting with not initilazing member variables
	this->pObjectManager = pObjectManager;
	this->pAsteroids = pAsteroids;
}

Player::~Player()
{

}

void Player::initialise(ObjectManager* pObjectManager, Rock* pAsteroids)
{
	//Repeating basically the same as Constructor just making sure Everything is set 
	//On the chance that the Constructor Fails all values will be set here anyway
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	RockImageSize = 0.0f;
	LoadImage(L"spaceship.bmp");
	this->pObjectManager = pObjectManager;
	this->pAsteroids = pAsteroids;
	shootDelay = 0;
}

void Player::update(float frameTime)
{
	//Allowing the Player to move endlessly 
	//MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue + 0.0f, -position.YValue + 0.0f));
	WrapScreen();

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
	//If the Image Size is 1 (big rock) want player to die
	//Otherwise rock will bounce off / collide with player
	if (typeid(other) == typeid(Rock))
	{
		//Get The Size
		GetAsteroidSize();
		if(RockImageSize == 1.0f)
		{
			isActive = false;
			Explosion* pExplosion = new Explosion();
			pExplosion->initialise(position);
			pObjectManager->addObject(pExplosion);
		}
		else
		{
			//Creating a Vector for the Normal
			Vector2D normal = (position - other.getPosition()).unitVector();
			if (normal * velocity < 0)
			{
				velocity = velocity - 2 * (velocity * normal) * normal;
				velocity = velocity * 0.6f;
			}
		}
	}

	if (typeid(other) == typeid(EnemyShip) || typeid(other) == typeid(Mines))
	{
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
	}

	if (typeid(other) == typeid(ArcadeMachine))
	{
		isActive = false;
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

float Player::getAngle()
{
	return angle;
}

float Player::GetAsteroidSize()
{
	RockImageSize = pAsteroids->GetImageSize();
	return RockImageSize;
}