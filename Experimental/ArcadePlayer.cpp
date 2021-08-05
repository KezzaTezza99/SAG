#include "ArcadePlayer.h"
#include "myinputs.h"
#include "AsteroidArcadeMachine.h"
#include "SpaceInvadersArcadeMachine.h"

const float cAcceleration = 200.0f;	
const float cFriction = 0.5f;
const float cTurnSpeed = 1.0f;

ArcadePlayer::ArcadePlayer()
{
	this->pGameManager = pGameManager;
	this->pAsteroids = pAsteroids;
	this->pSpaceInvaders = pSpaceInvaders;
    position.set(0, 0);
}

ArcadePlayer::~ArcadePlayer() {}

void ArcadePlayer::initialise(GameManager* pGameManager, AsteroidArcadeMachine* pAsteroids, SpaceInvadersArcadeMachine* pSpaceInvaders)
{
	this->pGameManager = pGameManager;
	this->pAsteroids = pAsteroids;
	this-> pSpaceInvaders = pSpaceInvaders;
    position.set(0, 0);
    velocity.set(0, 0);
	LoadImage(L"enemy.bmp");
}

void ArcadePlayer::update(float frameTime)
{
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
}

IShape2D& ArcadePlayer::GetShape()
{
    collisionShape.PlaceAt(position, 50.0f);
    return collisionShape;
}

void ArcadePlayer::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(AsteroidArcadeMachine))
	{
		//Sets itself to Deactive to be removed from the game
		Deactivate();
		//Sets the Game Manager to Deactive so it can also be removed from the game 
		//No longer needed once the Specific Level Manager is created
		pGameManager->Deactivate();
		//As player selected Asteroids need to Delete Space Invaders
		pSpaceInvaders->Deactivate();
	}

	if (typeid(other) == typeid(SpaceInvadersArcadeMachine))
	{
		//Doing same as above but deleting Asteroids as Player chose Space Invaders
		Deactivate();
		pGameManager->Deactivate();
		pAsteroids->Deactivate();
	}
}

void ArcadePlayer::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}