#include "EnemyShip.h"
#include "AsteroidPlayer.h"
#include "myinputs.h"
#include "Bullet.h"
#include <typeinfo>
#include "Rock.h"
#include "Explosion.h"
#include "vector2D.h"

const float cFriction = 0.5f;
const float BULLETSPEED = 600.0f;

EnemyShip::EnemyShip()
{
	velocity.set(0, 0);
	angle = 0;
	shootDelay = 0;
	countDown = 0;

	this->pObjectManager = pObjectManager;	//This is here to stop a warning i was getting with not initilazing member variables
	this->pThePlayer = pThePlayer;
}

EnemyShip::~EnemyShip()
{

}

void EnemyShip::initialise(ObjectManager* pObjectManager, AsteroidPlayer* pThePlayer, Vector2D randomStartPosition)
{
	position = randomStartPosition;
	velocity.set(0, 0);
	angle = 0;
	LoadImage(L"enemy.bmp");

	this->pObjectManager = pObjectManager;
	this->pThePlayer = pThePlayer;
	shootDelay = 0;
	countDown = 2;
}

void EnemyShip::update(float frameTime)
{
	//Let Enemy Wrap Screene
	WrapScreen();

	//Add Physics to movement like player movement?
	if (pThePlayer->checkIfActive() == true)
	{
		//Ship will always move and look towards the Player
		//When player dies need to stop looking at player because causes null pointer
		Vector2D PlayerPosition = pThePlayer->getPosition() - position;
		angle = PlayerPosition.angle();
		position = position + PlayerPosition * frameTime;
	}
	else
	{
		//When Player dies slowly slow the enemy down to a stop
		velocity = velocity - velocity * cFriction * frameTime;
	}

	//Dont want the enemy to shoot straight away - also fixes issue of enemy killing themselves by 
	//catching up to the bullet. Could fix this properly? Think the random veloicty given is to fast to start
	//Enemy Shoots at Asteroid Player

	countDown = countDown - frameTime;
	if (countDown <= 0 && shootDelay <= 0 && pThePlayer->checkIfActive() == true) 
	{
		Bullet* pBullet = new Bullet();
		if (pBullet)
		{
			Vector2D vel;
			vel.setBearing(angle, BULLETSPEED);
			Vector2D offset;
			offset.setBearing(angle, 60.0f);
			pBullet->initialise(position + offset, velocity + vel);

			if (pObjectManager)
			{
				pObjectManager->addObject(pBullet);
				shootDelay = 1.5f;	
				countDown = 0;
			}
		}
	}
	//Adding a timer to count down before allowing us to shoot again
	shootDelay = shootDelay - frameTime;
}

IShape2D& EnemyShip::GetShape()
{
	collisionShape.PlaceAt(position, 50.0f);
	return collisionShape;
}

void EnemyShip::HandleCollision(GameObject& other)
{
	//If Enemy Ship collides with Rock it will dissapear
	if (typeid(other) == typeid(Rock))
	{
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
	}

	//If collides with Bullet it will Dissapear 
	if (typeid(other) == typeid(Bullet))
	{
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
	}
}

void EnemyShip::DrawCollision()
{
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

Vector2D EnemyShip::getPosition()
{
	return position;
}


