#include "ArcadePlayer.h"
#include "myinputs.h"
#include "ArcadeMachine.h"

//TODO FIX MEMORY LEAKS
//FIX LEVEL MANAGER AND THE ARCADE MACHINE 
//Game manager creates arcade level and arcade player?

const float cAcceleration = 200.0f;	
const float cFriction = 0.5f;
const float cTurnSpeed = 1.0f;

ArcadePlayer::ArcadePlayer()
{
	this->pGameManager = pGameManager;
    position.set(0, 0);
}

ArcadePlayer::~ArcadePlayer()
{
}

void ArcadePlayer::initialise(GameManager* pGameManager)
{
	this->pGameManager = pGameManager;

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
	if (typeid(other) == typeid(ArcadeMachine))
	{
		Deactivate();
		pGameManager->Deactivate();
	}
}

void ArcadePlayer::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}

void ArcadePlayer::Deactivate()
{
	isActive = false;
}