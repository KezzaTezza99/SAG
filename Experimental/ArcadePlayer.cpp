//Author: w18024358
//Purpose: Implementing the necessary code to allow all the functionallity needed for the Player
#include "ArcadePlayer.h"
#include "myinputs.h"

const float cAcceleration = 200.0f;	
const float cFriction = 0.5f;
const float cTurnSpeed = 1.0f;

ArcadePlayer::ArcadePlayer()
{
	//Setting member variables
	this->pGameManager = pGameManager;
	this->pAsteroids = pAsteroids;
	this->pSpaceInvaders = pSpaceInvaders;
	this->pHunted = pHunted;
    position.set(0, 0);
}

void ArcadePlayer::Initialise(GameManager* pGameManager, AsteroidArcadeMachine* pAsteroids,
								SpaceInvadersArcadeMachine* pSpaceInvaders, HuntedArcadeMachine* pHunted)
{
	//Setting the Member Variables to equal the params 
	this->pGameManager = pGameManager;
	this->pAsteroids = pAsteroids;
	this-> pSpaceInvaders = pSpaceInvaders;
	this->pHunted = pHunted;
	
	//Resetting Position and Velocity to be 0
    position.set(0, 0);
    velocity.set(0, 0);
	LoadImage(L"enemy.bmp");						//Loading the Bitmap
}

void ArcadePlayer::Update(float frameTime)
{
	//Getting input from the Keyboard
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
	//Setting and placing the Collision shape
    collisionShape.PlaceAt(position, 50.0f);
    return collisionShape;
}

void ArcadePlayer::HandleCollision(GameObject& other)
{
	//Collisions
	if (typeid(other) == typeid(AsteroidArcadeMachine))
	{
		//Sets itself to Deactive to be removed from the game
		Deactivate();
		//Sets the Game Manager to Deactive so it can also be removed from the game 
		//No longer needed once the Specific Level Manager is created
		pGameManager->Deactivate();
		//As player selected Asteroids need to Delete Space Invaders
		pSpaceInvaders->Deactivate();
		//and Hunted
		pHunted->Deactivate();
	}

	if (typeid(other) == typeid(SpaceInvadersArcadeMachine))
	{
		//Doing same as above but deleting Asteroids as Player chose Space Invaders
		Deactivate();
		pGameManager->Deactivate();
		pAsteroids->Deactivate();
		pHunted->Deactivate();
	}

	if (typeid(other) == typeid(HuntedArcadeMachine))
	{
		Deactivate();
		pGameManager->Deactivate();
		pAsteroids->Deactivate();
		pSpaceInvaders->Deactivate();
	}
}

void ArcadePlayer::DrawCollision()
{
	//Useful Debug Info 
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}