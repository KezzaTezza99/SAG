//Author: w18024358
//Purpose: The purpose of the rock class is to spawn random rocks in random directions and speeds 
//that the player needs to avoid and destroy to gain score
#include "Rock.h"
#include "Bullet.h"
#include "AsteroidPlayer.h"
#include "RockDust.h"
#include "Explosion.h"
#include "Mines.h"

//TODO - Remove functionallity where small rocks bounce off player instead of blowing  up
//sometimes issues occure where they still kill player and sometimes they work as intended
//fix or remove

Rock::Rock()
{
	velocity.set(0, 0);
	this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
}

void Rock::Initialise(ObjectManager* pObjectManager, AsteroidsLevelManager* pLevelManager, 
	Vector2D startPosition, Vector2D startVelocity, float imageSize)
{
	position = startPosition;
	velocity = startVelocity;
	this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
	this->imageSize = imageSize;
	
	angle = 0;

	//Used to pick a Rock image from Rock 1 - 4
	int imageNumber = rand() % 4 + 1;

	if (imageNumber == 1)
	{
		LoadImage(L"rock1.bmp");
	}

	if (imageNumber == 2)
	{
		LoadImage(L"rock2.bmp");
	}

	if (imageNumber == 3)
	{
		LoadImage(L"rock3.bmp");
	}

	if (imageNumber == 4)
	{
		LoadImage(L"rock4.bmp");
	}
}

void Rock::Update(float frameTime)
{
	const float cTurnSpeed = 1.0f;

	WrapScreen();
	//A section of Players movement code makes a cool spinning effect
	angle = angle - cTurnSpeed * frameTime;								
	position = position + velocity * frameTime;
}

IShape2D& Rock::GetShape()
{
	const int OriginalRockCollisionSize = 66;

	//If the Rock Image Size is 1 then set collision shape to OG size else set to half
	if (GetImageSize() == 1.0f)
	{
		collisionShape.PlaceAt(position, OriginalRockCollisionSize);
		return collisionShape;
	}
	else
	{
		collisionShape.PlaceAt(position, OriginalRockCollisionSize / 2);
		return collisionShape;
	}
}

void Rock::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		//If the image size is one need todo some slightly different things
		if (GetImageSize() == 1.0f)
		{
			//Explosion
			Explosion* pExplosion = new Explosion();
			pExplosion->Initialise(position);
			pObjectManager->AddObject(pExplosion);
			//Deactivating
			Deactivate();
			//Spawning smaller Rocks at position
			SpawnRock(position);
			//Telling Level Manager that the Rock has been destroyed and score needs to be increased
			pLevelManager->EnemyDead(L"Asteroid");
			//Decreasing the current count of Asteroids to start next level when = 0
			pLevelManager->DecreaseAsteroidCount();
		}
		else
		{	
			//Dust Cloud instead of Explosion
			RockDust* pDust = new RockDust();
			pDust->Initialise(position, 1.5f);
			pObjectManager->AddObject(pDust);
			//Deactivating the Object
			Deactivate();
			//Telling Level Manager that a Small Asteroid has died (increases score differently)
			pLevelManager->EnemyDead(L"Small Asteroid");
		}
	}

	if (typeid(other) == typeid(Rock))
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (GetImageSize() == 1.0f)
		{
			//Bounce off each other
			if (normal * velocity < 0)
			{
				velocity = velocity - 2 * (velocity * normal) * normal;
				velocity = velocity * 0.6f;
			}
		}
		else
		{
			//Smaller rocks bounce away faster
			if (normal * velocity < 0)
			{
				velocity = velocity - 2 * (velocity * normal) * normal;
				velocity = velocity * 0.8f;
			}
		}
	}

	if (typeid(other) == typeid(Mines))
	{
		if (GetImageSize() == 1.0f)
		{
			//Deleting
			Deactivate();
			//Explosion
			Explosion* pExplosion = new Explosion();
			pExplosion->Initialise(position);
			pObjectManager->AddObject(pExplosion);
			pLevelManager->DecreaseAsteroidCount();
		}
		else
		{
			Deactivate();
			RockDust* pDust = new RockDust();
			pDust->Initialise(position, 1.0f);
			pObjectManager->AddObject(pDust);
		}
	}

	//Instead of Smaller Rocks bouncing off the Player due to issues
	//big rocks will blow player up but will break into smaller rocks and "bounce away" from Explosion
	//smaller rocks will blow up player now but will also be destroyed into a cloud of dust
	if (typeid(other) == typeid(AsteroidPlayer))
	{
		if (GetImageSize() == 1.0f)
		{
			//Rock moves back slightly then is destoryed?
			Vector2D normal = (position - other.GetPosition()).unitVector();
			if (normal * velocity < 0)
			{
				velocity = velocity - 2 * (velocity * normal) * normal;
				velocity = velocity * 0.6f;
			}
			//Removing the Rock
			Deactivate();
			//Explosion
			Explosion* pExplosion = new Explosion();
			pExplosion->Initialise(position);
			pObjectManager->AddObject(pExplosion);
			//Spawning smaller rocks
			SpawnRock(position);
			pLevelManager->DecreaseAsteroidCount();
		}
		else
		{
			Deactivate();
			RockDust* pDust = new RockDust();
			pDust->Initialise(position, 2.0f);
			pObjectManager->AddObject(pDust);
		}
	}
}

void Rock::DrawCollision()
{
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Rock::SpawnRock(Vector2D position)
{
	//Using this value to decide on how many asteroids spawn to replace damaged rock
	int randomNumber = rand() % 5 + 1;
						
	if (imageSize > 0.5)
	{
		for (int i = 0; i < randomNumber; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D newPosition = position + Vector2D((rand() % 150 - 75) * imageSize, (rand() % 150 - 75) * imageSize);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->Initialise(&*pObjectManager, &*pLevelManager, newPosition, randomVelocity, imageSize / 2.0f);
			pObjectManager->AddObject(pRocks);
		}
	}
}