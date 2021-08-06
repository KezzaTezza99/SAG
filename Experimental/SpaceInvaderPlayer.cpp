#include "SpaceInvaderPlayer.h"
#include "myinputs.h"
#include "SpaceInvaderEnemyBullet.h"
#include "SpaceInvaderBullet.h"

//Due to having two bullet types it increases cohesion need to fix

const float cAcceleration = 400.0f;
const float cFriction = -0.5f;
const float BULLETSPEED = 800.0f;

SpaceInvaderPlayer::SpaceInvaderPlayer()
{
    position.set(0, -850);
    velocity.set(0, 0);
	friction.set(0, 0);
	shootDelay = 0.0f;
    this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
}

SpaceInvaderPlayer::~SpaceInvaderPlayer()
{
}

void SpaceInvaderPlayer::initialise(ObjectManager* pObjectManager, SpaceInvaderLevelManager* pLevelManager, Vector2D startPosition)
{
	Rectangle2D playingArea = MyDrawEngine::GetInstance()->GetViewport();

    this->pObjectManager = pObjectManager;
	this->pLevelManager = pLevelManager;
	position.set(startPosition);
    velocity.set(0, 0);
	friction.set(0, 0);
	shootDelay = 0.0f;
    LoadImage(L"harrasser.bmp");

	//Making the Ship half the size
	imageSize = 0.5f;
}

void SpaceInvaderPlayer::update(float frameTime)
{
	//Can Wrap Screen - Change this so you cannot wrap screen but also not go off screen
	WrapScreen();

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	if (pInputs->KeyPressed(DIK_A))
	{
		acceleration.set(-cAcceleration, 0);
		velocity = velocity + acceleration * frameTime;
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		acceleration.set(cAcceleration, 0);
		velocity = velocity + acceleration * frameTime;
	}
	friction = cFriction * velocity;
	velocity = velocity  + friction * frameTime;
	position = position + velocity * frameTime;

	//Same Shooting code as Asteroid Player just slightly different Variables
	if (pInputs->KeyPressed(DIK_SPACE) && shootDelay <= 0)	//Only allowed to shoot when shoot delay is 0
	{
		SpaceInvaderBullet* pBullet = new SpaceInvaderBullet();
		if (pBullet)
		{
			Vector2D vel;
			vel.setBearing(angle, BULLETSPEED);
			Vector2D offset;	//This will make the bullets appear in front of AsteroidPlayer not centre
			offset.setBearing(angle, 55.0f);
			pBullet->initialise(position + offset, vel + velocity);
			if (pObjectManager)
			{
				pObjectManager->addObject(pBullet);
				shootDelay = 0.8f;
			}
		}
	}
	//Adding a timer to count down before allowing us to shoot again
	shootDelay = shootDelay - frameTime;
}

IShape2D& SpaceInvaderPlayer::GetShape()
{
    collisionShape.PlaceAt(position, 60);
    return collisionShape;
}

void SpaceInvaderPlayer::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(SpaceInvaderEnemyBullet))
	{
		//Sending last location to Level Manager to Spawn another version at same location
		pLevelManager->GetPlayerPosition(position);
		
		//Deleting Self
		Deactivate();
		
		//Telling the Level Manager player has died 
		pLevelManager->playerDead();
	}
}

void SpaceInvaderPlayer::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
    MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}
