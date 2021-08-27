//Author: w18024358
//Purpose: Spawn a player that can kill and be killed by the Enemy Ship
#include "HuntedPlayer.h"
#include "myinputs.h"
#include "Explosion.h"
#include "Bullet.h"

HuntedPlayer::HuntedPlayer()
{
    this->pObjectManager = pObjectManager;
	this->pParticles = pParticles;
    position.set(0, 0);
	velocity.set(0, 0);
	boostTimer = 2.0f;								//Experiment with values
	shootDelay = 1.0f;
}

void HuntedPlayer::Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles)
{
    this->pObjectManager = pObjectManager;
	this->pParticles = pParticles;
    position.set(0, 0);
	velocity.set(0, 0);
    LoadImage(L"spaceship.bmp");
	boostTimer = 2.0f;
	shootDelay = 1.0f;
}

void HuntedPlayer::Update(float frameTime)
{
	//Some useful variables I'll need for Movement and Shooting
	const float cAcceleration = 300.0f;
	const float cFriction = 0.5f;
	const float cTurnSpeed = 1.8f;
	const float cBoostedAcceleration = 450.0f;
	const float BULLETSPEED = 900.0f;

	//Adding a timer to count down before allowing us to shoot again
	shootDelay -= frameTime;

	//Hunted Player will be able to "endlessly" move around the Map
	//camera follows player
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(position.XValue + 0.0f, -position.YValue + 0.0f));
	
	//Getting input from keyboard
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
	if (pInputs->KeyPressed(DIK_LSHIFT))
	{
		boostTimer -= frameTime;
		if (boostTimer > 0.0f)
		{
			acceleration.setBearing(angle, cBoostedAcceleration);
			velocity = velocity + acceleration * frameTime;

			//Drawing Flame behind the Ship too give a boost like effect
			Explosion* pExplosion = new Explosion();
			Vector2D behindShip;
			behindShip.setBearing(angle + 3.14f, 32.0f);					
			behindShip = behindShip + position;
			Vector2D shipVel;
			shipVel.setBearing(angle + 3.14f, 500.0f);
			shipVel = shipVel + velocity;
			pExplosion->Initialise(behindShip, 0.6f, 50.0f, shipVel);
			pObjectManager->AddObject(pExplosion);
		}
		if (boostTimer <= 0.0f)
			boostTimer = 2.0f;
	}
	velocity = velocity - velocity * cFriction * frameTime;
	position = position + velocity * frameTime;

	//Shooting
	if (pInputs->KeyPressed(DIK_SPACE) && shootDelay <= 0)	//Only allowed to shoot when shoot delay is 0
	{
		Bullet* pBullet = new Bullet();
		if (pBullet)
		{
			Vector2D vel;
			vel.setBearing(angle, BULLETSPEED);
			Vector2D offset;	//This will make the bullets appear in front of AsteroidPlayer not centre
			offset.setBearing(angle, 45.0f);
			pBullet->Initialise(position + offset, vel + velocity);
			if (pObjectManager)
			{
				pObjectManager->AddObject(pBullet);
				shootDelay = 0.5f;	//Setting to 0.5 every time we have shot one bullet
			}
		}
	}
}

IShape2D& HuntedPlayer::GetShape()
{
	collisionShape.PlaceAt(position, 32.0f);
	return collisionShape; 
}

void HuntedPlayer::HandleCollision(GameObject& other) 
{
	if (typeid(other) == typeid(Bullet))
	{
		//If Player has been shot then Deactivating the Player
		Deactivate();
		//Causing an Explosion
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(position);
		pObjectManager->AddObject(pExplosion);
		//Creating a bunch of Particles
		pParticles->AddParticles(position, 800.0f, MyDrawEngine::YELLOW, 20);
		pParticles->AddParticles(position, 700.0f, MyDrawEngine::RED, 10);
	}
}

void HuntedPlayer::DrawCollision() 
{
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}