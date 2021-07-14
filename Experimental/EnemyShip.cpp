#include "EnemyShip.h"
#include "AsteroidPlayer.h"
#include "myinputs.h"
#include "Bullet.h"
#include <typeinfo>
#include "Rock.h"
#include "Explosion.h"
#include "vector2D.h"

const float cAcceleration = 100.0f;
//const float cGravity = 250.0f;	
const float cFriction = 0.5f;
const float cTurnSpeed = 0.8f;
const float BULLETSPEED = 400.0f;

EnemyShip::EnemyShip()
{
	velocity.set(0, 0);
	angle = 0;
	shootDelay = 0;

	this->pObjectManager = pObjectManager;	//This is here to stop a warning i was getting with not initilazing member variables
	this->pThePlayer = pThePlayer;
}

EnemyShip::~EnemyShip()
{

}

void EnemyShip::initialise(ObjectManager* pObjectManager, AsteroidPlayer* pThePlayer, Vector2D randomStartPosition)
{
	position = randomStartPosition;
	currentPosition = position;
	velocity.set(0, 0);
	angle = 0;
	LoadImage(L"enemy.bmp");

	this->pObjectManager = pObjectManager;
	this->pThePlayer = pThePlayer;
	shootDelay = 0;

	wait = 0.2f;
}

void EnemyShip::update(float frameTime)
{
	////THIS MAKES IT SPIN LIKE CRAZY MAYBE ADD THIS TO THE ASTEROIDS?
	//double PI = atan(1) * 4;
	//angle = float(atan2(playerPos.XValue - position.XValue, playerPos.YValue - position.YValue) * (180 / PI));
	//Vector2D angleVec;
	//angleVec.set(angle, 0.0001f);
	//velocity = velocity + angleVec * frameTime;
	//Vector2D directonOfPlayer = playerPos - position + velocity * frameTime;
	//position = position + directonOfPlayer * frameTime;
	
	////OLD CODE THAT KINDA WORKS -------------------------------------------------------
	//Vector2D playerAngle = playerPos.unitVector();
	//Vector2D shipAngle = position.unitVector();
	//Vector2D angleNeeded = playerAngle - shipAngle;
	//velocity = velocity - angleNeeded * frameTime;
	//Vector2D directionOfPlayer = playerPos - position + velocity * frameTime;
	//position = position + directionOfPlayer * frameTime;
	////---------------------------------------------------------------------------------

	//ENEMY REPLICATES AsteroidPlayer MOVEMENT
	//acceleration.setBearing(angle, cAcceleration);
	//velocity = velocity + acceleration * frameTime;
	//if (playerAngle <= angle)
	//{
	//	angle = angle - cTurnSpeed * frameTime;
	//}

	//if (playerAngle >= angle)
	//{
	//	angle = angle + cTurnSpeed * frameTime;
	//}
	//velocity = velocity - velocity * cFriction * frameTime;
	//position = position + velocity * frameTime;
	//---------------------------------------------------------
	 
	//Vector2D directonOfPlayer = playerPos - position + velocity * frameTime;

	//acceleration.setBearing(angle, cAcceleration);
	//velocity = velocity + acceleration * frameTime;

	//wait -= frameTime;
	//
	//if (angle < playerAngle)
	//{
	//	if (wait <= 0.00f)
	//	{
	//		angle = angle + cTurnSpeed * frameTime;
	//		wait = 0.05f;
	//	}
	//}

	//if (angle > playerAngle)
	//{
	//	if (wait <= 0.00f)
	//	{
	//		angle = angle - cTurnSpeed * frameTime;
	//		wait = 0.05f;
	//	}
	//}
	//velocity = velocity - velocity * cFriction * frameTime;
	//position = position + directonOfPlayer * frameTime;
	
	//FIGURE OUT HOW TO MAKE ENEMY LOOK TOWARDS THE AsteroidPlayer
	//angle = playerAngle;
	//angle = (position.angle() - playerPos.angle()) * cTurnSpeed;
	//Vector2D directonOfPlayer = playerPos - position + velocity * frameTime;
	//acceleration.setBearing(angle, cAcceleration);
	//velocity = velocity + acceleration * frameTime;
	//position = position + directonOfPlayer * frameTime;

	//Only Get the players position if the AsteroidPlayer is Alive
	//Without the check it crashes 
	if (pThePlayer->checkIfActive() == true)	//pThePlayer->checkIfActive() still causes issues
	{
		getPlayer();
	}

	// ENEMY SHOOT AsteroidPlayer
	/*if (shootDelay <= 0)	//Only allowed to shoot when shoot delay is 0
	{
		Bullet* pBullet = new Bullet();
		if (pBullet)
		{
			Vector2D vel;
			vel.setBearing(playerAngle, BULLETSPEED);
			Vector2D offset;	//This will make the bullets appear in front of AsteroidPlayer not centre
			offset.setBearing(playerAngle, 65.0f);
			pBullet->initialise(position + offset, vel + velocity);

			if (pObjectManager)
			{
				pObjectManager->addObject(pBullet);
				shootDelay = 0.5f;	//Setting to 0.5 every time we have shot one bullet
			}
		}
	}
	//Adding a timer to count down before allowing us to shoot again
	shootDelay = shootDelay - frameTime; */
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

	currentPosition = getPosition();
}

void EnemyShip::getPlayerPosition()
{
	
}

void EnemyShip::getPlayer()
{
	if (pThePlayer)
	{
		playerPos = pThePlayer->getPosition();
		playerAngle = pThePlayer->getAngle();
	}
}


