//Author: w18024358
//Purpose: Implement the necessary code to implement all the Asteroid Players functionallity
#include "AsteroidPlayer.h"
#include "myinputs.h"
#include "Bullet.h"
#include "Rock.h"
#include "Explosion.h"
#include "Mines.h"

//Need other Entities to know about Players location to stop entities spawning randomly on top or near player
AsteroidPlayer::AsteroidPlayer()
{
	//Initilising all the Variables
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	shootDelay = 0;
	RockImageSize = 0.0f;
	//This is here to stop a warning I was getting with not initilazing member variables
	this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
}

void AsteroidPlayer::Initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager)
{
	//Repeating basically the same as Constructor just making sure Everything is set 
	//On the chance that the Constructor Fails all values will be set here anyway
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	RockImageSize = 0.0f;
	LoadImage(L"spaceship.bmp");
	this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
	shootDelay = 0;
}

void AsteroidPlayer::Update(float frameTime)
{
	const float cAcceleration = 400.0f;
	const float cFriction = 0.5f;
	const float cTurnSpeed = 1.5f;
	const float BULLETSPEED = 500.0f;

	//Allowing the Player to Wrap the Screen
	WrapScreen();
	
	//Getting Keyboard Input
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
	//Only allowed to shoot when space is pressed and when shoot delay is 0
	if (pInputs->KeyPressed(DIK_SPACE) && shootDelay <= 0)	
	{
		Bullet* pBullet = new Bullet();
		if(pBullet)
		{
			Vector2D vel;
			vel.setBearing(angle, BULLETSPEED);
			Vector2D offset;						//This will make the bullets appear in front and not centre
			offset.setBearing(angle, 45.0f);
			pBullet->Initialise(position + offset, vel + velocity);
			if (pObjectManager)
			{
				pObjectManager->AddObject(pBullet);
				shootDelay = 0.5f;					//Setting to 0.5 every time we have shot one bullet
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
	if (typeid(other) == typeid(Rock) || typeid(other) == typeid(Mines))
	{
		//Deactivating the Player if it collides with anything
		Deactivate();
		//Creating an Explosion
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(position);
		pObjectManager->AddObject(pExplosion);
		//Telling Level Manager the Game is Over as the Player has died - This will change if I implement health / lives
		pLevelManager->GameOver();
	}
}

void AsteroidPlayer::DrawCollision()
{
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}