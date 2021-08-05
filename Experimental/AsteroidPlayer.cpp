#include "AsteroidPlayer.h"
#include "myinputs.h"
#include "Bullet.h"
#include <typeinfo>
#include "Rock.h"
#include "EnemyShip.h"
#include "Explosion.h"
#include "Mines.h"
#include "AsteroidArcadeMachine.h"

const float cAcceleration = 200.0f;	
//const float cGravity = 250.0f;	
const float cFriction = 0.5f;	
const float cTurnSpeed = 1.0f; 
const float BULLETSPEED = 400.0f;

AsteroidPlayer::AsteroidPlayer()
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

AsteroidPlayer::~AsteroidPlayer()
{
}

void AsteroidPlayer::initialise(ObjectManager* pObjectManager, Rock* pAsteroids)
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

void AsteroidPlayer::update(float frameTime)
{
	//Allowing the AsteroidPlayer to move endlessly 
	//MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue + 0.0f, -position.YValue + 0.0f));
	WrapScreen();

	//Keep getting the Asteroids size? May fix the occusional small rock killing me
	pAsteroids->GetImageSize();

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
			Vector2D offset;	//This will make the bullets appear in front of AsteroidPlayer not centre
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

IShape2D& AsteroidPlayer::GetShape()
{
	collisionShape.PlaceAt(position, 30.0f);
	return collisionShape;
}

void AsteroidPlayer::HandleCollision(GameObject& other)
{
	//If the Image Size is 1 (big rock) want AsteroidPlayer to die
	//Otherwise rock will bounce off / collide with AsteroidPlayer
	if (typeid(other) == typeid(Rock))
	{
		if (pAsteroids)
		{
			//Get The Size
			/*GetAsteroidSize()*/
			if (pAsteroids->GetImageSize() == 1.0f)
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
	}

	if (typeid(other) == typeid(EnemyShip) || typeid(other) == typeid(Mines))
	{
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
	}

	if (typeid(other) == typeid(AsteroidArcadeMachine))
	{
		isActive = false;
	}
}

void AsteroidPlayer::DrawCollision()
{
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

Vector2D AsteroidPlayer::getPosition()
{
	return position;
}

bool AsteroidPlayer::isDead() const
{
	return isActive;
}

float AsteroidPlayer::getAngle()
{
	return angle;
}