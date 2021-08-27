//Author: w18024358
//Purpose: To place the Aracade machine in the arcade and provide collision code that will start the Hunted Game
//Mode once the Player interacts with it
#include "HuntedArcadeMachine.h"
#include "ArcadePlayer.h"
#include "HuntedLevelManager.h"

HuntedArcadeMachine::HuntedArcadeMachine()
{
	this->pObjectManager = pObjectManager;
	this->pParticles = pParticles;
	position.set(0, 500);
	startHunted = false;
}

void HuntedArcadeMachine::Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles)
{
	this->pObjectManager = pObjectManager;
	this->pParticles = pParticles;
	position.set(0, 500);

	startHunted = false;
	LoadImage(L"HuntedMachine.png");
}

void HuntedArcadeMachine::Update(float frameTime)
{
	if (startHunted)
	{
		//Adding the Hunted Level Manager to the Game as the Player has chosen to play Hunted
		HuntedLevelManager* pLevelManager = new HuntedLevelManager();
		pLevelManager->Initialise(&*pObjectManager, pParticles);
		pObjectManager->AddObject(pLevelManager);

		//Deactivating the Arcade Machine
		Deactivate();
	}
}

IShape2D& HuntedArcadeMachine::GetShape()
{
	collisionShape.PlaceAt(position, 200.0f);
	return collisionShape;
}

void HuntedArcadeMachine::DrawCollision()
{
	MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
}

void HuntedArcadeMachine::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(ArcadePlayer))
	{
		startHunted = true;
	}
}
