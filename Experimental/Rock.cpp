#include "Rock.h"
#include "Bullet.h"
#include "AsteroidPlayer.h"
#include "RockDust.h"
#include "Explosion.h"
#include "Mines.h"

/* TODO
			make the dust cloud bigger but then get smaller
			make AsteroidPlayer and rock bounce when rock big but smaller rocks only bounce of AsteroidPlayer
			no effect on AsteroidPlayer at all from small rocks
			smaller rocks get destroyed by bigger ones??
			As levels increase add smaller rocks randomly to begin with?
			Add bombs ??
			event system?
*/

const float cTurnSpeed = 1.0f;
const float angle = 0.0f;
const int OriginalRockCollisionSize = 66;

Rock::Rock()
{
	velocity.set(0, 0);
	this->pObjectManager = pObjectManager;
}

Rock::~Rock() {}

void Rock::initialise(ObjectManager* pObjectManager, Vector2D startPosition, Vector2D startVelocity, float imageSize)
{
	position = startPosition;
	velocity = startVelocity;
	this->pObjectManager = pObjectManager;
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

void Rock::update(float frameTime)
{
	WrapScreen();
	//A section of Players movement code makes a cool spinning effect
	angle = angle - cTurnSpeed * frameTime;								//TODO Make Faster Asteroids spin faster
	position = position + velocity * frameTime;
}

IShape2D& Rock::GetShape()
{
	//If the image size is 1 (default) then the collision shape will be the Original size
	//this size fits the bigger rocks, once the rock is damaged by AsteroidPlayer it splits up
	//the image size for level 2 rock is half the size so now the collision shape
	//is also reduced by half to represent a smaller collision surface for the smaller rock
	//this goes on once again for the final rock which is now 1/4 of the original size
	if (imageSize == 1.0f)
	{
		collisionShape.PlaceAt(position, OriginalRockCollisionSize);
		return collisionShape;
	}
	else if(imageSize == 0.5f)
	{
		collisionShape.PlaceAt(position, OriginalRockCollisionSize / 2);
		return collisionShape;
	}
	else
	{
		collisionShape.PlaceAt(position, OriginalRockCollisionSize / 4);
		return collisionShape;
	}
}

void Rock::HandleCollision(GameObject& other)
{
	//If the Asteroid collides with another it will Bounce
	//If the rock has been broken
	if (typeid(other) == typeid(Rock) || typeid(other) == typeid(AsteroidPlayer))
	{
		//Creating a Vector for the Normal
		Vector2D normal = (position - other.getPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
			velocity = velocity * 0.6f;
		}
	}

	if (typeid(other) == typeid(Mines))
	{
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
	}

	//If the Asteroid collids with a Bullet then Deactive the Asteroid
	if(typeid(other) == typeid(Bullet))
	{
		//Creating a Dust effect
		//Bigger Rocks produce bigger cloud of dust to smaller rocks
		if (GetImageSize() == 1.0f)
		{
			RockDust* pRockDust = new RockDust();
			pRockDust->initialise(position, 1.5f);
			pObjectManager->addObject(pRockDust);
		}
		else if (GetImageSize() == 0.5f)
		{
			RockDust* pRockDust = new RockDust();
			pRockDust->initialise(position, 1.0f);
			pObjectManager->addObject(pRockDust);
		}
		else
		{
			RockDust* pRockDust = new RockDust();
			pRockDust->initialise(position, 0.5f);
			pObjectManager->addObject(pRockDust);
		}

		//Sets the Asteroid to not active which makes it dissapear 
		isActive = false;	//The Object Manager will then delete from Game 
		SpawnRock(position);
	}

	if (typeid(other) == typeid(Mines))
	{
		//Blow up then create smaller rocks that shoot of in random directions at a high speed randomly
		isActive = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->initialise(position);
		pObjectManager->addObject(pExplosion);
		SpawnRock(position);
	}
}

void Rock::DrawCollision()
{
	//Used for Debugging Purposes - Shows the Hit Boxes when I press H
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

void Rock::SpawnRock(Vector2D position)
{
	//Using this value to decide on how many asteroids spawn to replace damaged rock
	int randomNumber = rand() % 6 + 2;

	//Spawning some rocks to break the Asteroid into multiple 
	//Using the random number again to mix it up every time
	//Only do it if the image is above a certain size 
	if (imageSize > 0.4f)										//Will create two new generations of rock before < 0.4 
	{
		for (int i = 0; i < randomNumber; i++)
		{
			Rock* pRocks = new Rock();
			Vector2D newPosition = position + Vector2D((rand() % 150 - 75) * imageSize, (rand() % 150 - 75) * imageSize);
			Vector2D randomVelocity(float(rand() % 600 - 100), float(rand() % 600 - 100));
			pRocks->initialise(&*pObjectManager, newPosition, randomVelocity, imageSize / 2.0f);
			pObjectManager->addObject(pRocks);
		}
	}
}

Vector2D Rock::getPosition()
{
	return position;
}

float Rock::GetImageSize()
{
	return imageSize;
}