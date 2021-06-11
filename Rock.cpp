#include "Rock.h"
#include "Bullet.h"
#include "Player.h"
#include "RockDust.h"
#include "Explosion.h"

const float cTurnSpeed = 1.0f;
const float angle = 0.0f;

Rock::Rock()
{
	velocity.set(0, 0);
	this->pObjectManager = pObjectManager;
}

Rock::~Rock()
{

}

void Rock::initialise(ObjectManager* pObjectManager, Vector2D startPosition, Vector2D startVelocity)
{
	position = startPosition;
	velocity = startVelocity;
	this->pObjectManager = pObjectManager;

	//Need to Decide on Rock 1-4 by randomly choosing a Number
	int imageNum = rand() % 4 + 1;

	if (imageNum == 1)
	{
		LoadImage(L"rock1.bmp");
	}

	if (imageNum == 2)
	{
		LoadImage(L"rock2.bmp");
	}

	if (imageNum == 3)
	{
		LoadImage(L"rock3.bmp");
	}

	if (imageNum == 4)
	{
		LoadImage(L"rock4.bmp");
	}
}

void Rock::update(float frameTime)
{
	//A section of Players movement code makes a cool spinning effect
	angle = angle - cTurnSpeed * frameTime;		//TODO Make Faster Asteroids spin faster
	
	position = position + velocity * frameTime;
}

IShape2D& Rock::GetShape()
{
	collisionShape.PlaceAt(position, 62);
	return collisionShape;
}

void Rock::HandleCollision(GameObject& other)
{
	//If the Asteroid collides with another it will Bounce
	if (typeid(other) == typeid(Rock))
	{
		//Creating a Vector for the Normal
		Vector2D normal = (position - other.getPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;		
			velocity = velocity * 0.6f;

			//RockDust* pRockDust = new RockDust();
			//pRockDust->initialise(position);
			//pObjectManager->addObject(pRockDust);
		}
	}

	//If the Asteroid collids with a Bullet then Deactive the Asteroid
	if(typeid(other) == typeid(Bullet))
	{
		//Sets the Asteroid to not active which makes it dissapear 
		isActive = false;	//The Object Manager will then delete from Game 
	}

	if (typeid(other) == typeid(Player))
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
void Rock::DrawCollision()
{
	//Used for Debugging Purposes - Shows the Hit Boxes when I press H
	//Shows the Collision Shape
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
	//Line Showing the Direction of Object
	MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}

Vector2D Rock::getPosition()
{
	return position;
}
