#include "EnemyShip.h"
#include "Player.h"
#include "myinputs.h"
#include "Bullet.h"
#include <typeinfo>
#include "Rock.h"

const float cAcceleration = 200.0f;
//const float cGravity = 250.0f;	
const float cFriction = 0.5f;
const float cTurnSpeed = 1.0f;
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

void EnemyShip::initialise(ObjectManager* pObjectManager, Player* pThePlayer, Vector2D randomStartPosition)
{
	position = randomStartPosition;
	velocity.set(0, 0);
	angle = 0;
	LoadImage(L"enemy.bmp");

	this->pObjectManager = pObjectManager;
	this->pThePlayer = pThePlayer;
	shootDelay = 0;
}

void EnemyShip::update(float frameTime)
{
	// LOOK AT PLAYER
	Vector2D playerAngle = playerPos.unitVector();
	Vector2D shipAngle = position.unitVector();

	Vector2D angleNeeded = playerAngle  - shipAngle;

	velocity = velocity - angleNeeded * frameTime;
	Vector2D directionOfPlayer = playerPos - position + velocity * frameTime;

	position = position + directionOfPlayer * frameTime;

	//Only Get the players position if the player is Alive
	//Without the check it crashes 
	if (pThePlayer->checkIfActive() == true)	//pThePlayer->checkIfActive() still causes issues
	{
		getPlayer();
	}

	// ENEMY SHOOT PLAYER
	/*if (shootDelay <= 0)	//Only allowed to shoot when shoot delay is 0
	{
		Bullet* pBullet = new Bullet();
		if (pBullet)
		{
			Vector2D vel;
			vel.setBearing(playerAngle, BULLETSPEED);
			Vector2D offset;	//This will make the bullets appear in front of Player not centre
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
	}

	//If collides with Bullet it will Dissapear 
	if (typeid(other) == typeid(Bullet))
	{
		isActive = false;
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

void EnemyShip::getPlayerPosition()
{
	
}

void EnemyShip::getPlayer()
{
	if (pThePlayer)
	{
		playerPos = pThePlayer->getPosition();
	}
}


