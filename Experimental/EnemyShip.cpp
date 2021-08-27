//Author: w18024358
//Purpose: Implement the necessary functionallity for the Enemy Ship 
#include "EnemyShip.h"
#include "Bullet.h"
#include "Explosion.h"

EnemyShip::EnemyShip()
{
	velocity.set(0, 0);
	angle = 0;
	shootDelay = 3.0f;
	countDown = 3.0f;

	this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
	this->pThePlayer = pThePlayer;
	this->pParticles = pParticles;
}

void EnemyShip::Initialise(ObjectManager* pObjectManager, HuntedLevelManager* pLevelManager, 
	HuntedPlayer* pThePlayer, Vector2D randomStartPosition, ParticleSystem* pParticles)
{
	position = randomStartPosition;
	velocity.set(0, 0);
	angle = 0;
	LoadImage(L"enemy.bmp");

	this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
	this->pThePlayer = pThePlayer;
	this->pParticles = pParticles;
	shootDelay = 3.0f;
	countDown = 3.0f;
}

void EnemyShip::Update(float frameTime)
{
	const float cFriction = 0.5f;
	const float BULLETSPEED = 850.0f;

	//Add Physics to movement like player movement?
	//If the Player is still Alive then move towards them without this will get crashes
	if (pThePlayer->CheckIfActive() == true)
	{
		//Ship will always move and look towards the Player
		//When player dies need to stop looking at player because causes null pointer
		Vector2D PlayerPosition = pThePlayer->GetPosition() - position;
		angle = PlayerPosition.angle();
		position = position + PlayerPosition * frameTime;
	}
	
	//Dont want the enemy to shoot straight away - also fixes issue of enemy killing themselves by 
	//catching up to the bullet. Could fix this properly? Think the random velocity given is to fast to start
	//Enemy Shoots at Asteroid Player
	countDown = countDown - frameTime;
	if (countDown <= 0 && shootDelay <= 0 && pThePlayer->CheckIfActive() == true) 
	{
		Bullet* pBullet = new Bullet();
		if (pBullet)
		{
			Vector2D vel;
			vel.setBearing(angle, BULLETSPEED);
			Vector2D offset;
			offset.setBearing(angle, 60.0f);
			pBullet->Initialise(position + offset, velocity + vel);

			if (pObjectManager)
			{
				pObjectManager->AddObject(pBullet);
				shootDelay = 3.0f;	
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
	//If collides with Bullet it will Dissapear 
	if (typeid(other) == typeid(Bullet))
	{
		//Deleting the Ship
		Deactivate();
		//Creating Explosion
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(position);
		pObjectManager->AddObject(pExplosion);
		//Adding Particles for better effect
		pParticles->AddParticles(position, 800.0f, MyDrawEngine::YELLOW, 20);
		pParticles->AddParticles(position, 600.0f, MyDrawEngine::RED, 10);
		//Telling Level Manager they died
		pLevelManager->EnemyDead();
	}
}

void EnemyShip::DrawCollision()
{
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}