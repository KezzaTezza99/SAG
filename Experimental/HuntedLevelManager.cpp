//Author: w18024358
//Purpose: Implement the neccessary code to have a basic functional level manager that can
//start levels, end game, spawn entities
#include "HuntedLevelManager.h"
#include "Stars.h"
#include "EnemyShip.h"
#include "gamecode.h"

//Due to the Enemy Ship needing to know about the Player and the Enemy being created out of the scope of where the 
//player is created then I need to have a member variable of the Player that can be assigned the pointer of Player
//this allows the Enemy to have access to the Player which is necessary. 
//the problem comes when the Player needs to know about the Level Manager as it needs to tell it when it dies, the issue 
//with this is that the Level Manager needs to know about the Player in the Header File for the member variable but
//the player cant be created until the level manager has been created which causes issues
//player needs to be created before the level manager but the level manager creates the player so this is an issue
//with limited time I will just have to leave this incomplete for now... sorry Chris
HuntedLevelManager::HuntedLevelManager()
{
	this->pObjectManager = pObjectManager;
	this->pParticles = pParticles;
	this->pThePlayer = pThePlayer;
	startingTextTimer = 5.0f;
	timeAlive = 0.0f;
	playerDead = false;
	startGame = false;
	startingText = true;
	x = 0.0f;
	y = 0.0f;
}

void HuntedLevelManager::Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles)
{
	this->pObjectManager = pObjectManager;
	this->pParticles = pParticles;
	this->pThePlayer = pThePlayer;
	startingTextTimer = 5.0f;
	timeAlive = 0.0f;
	playerDead = false;
	startGame = false;
	startingText = true;
	x = 0.0f;
	y = 0.0f;

	//Creating the Player and Stars here so they can interact before the game starts
	//gives them a head start against Enemy Ships
	HuntedPlayer* pPlayer = new HuntedPlayer();
	pPlayer->Initialise(pObjectManager, pParticles);
	pObjectManager->AddObject(pPlayer);
	pThePlayer = pPlayer;							//Used to give the Enemy Ship reference to Player

	//Adding Stars
	for (int i = 0; i < 50; i++)
	{
		//TODO Need to make an effective way to create a vast amount of Stars very laggy to have 200ish
		//on this device - experiment with away when player is a set distance move all stars?
		Stars* pStars = new Stars();
		Vector2D randomPosition;
		float randomNumber = rand() % 5000 + 500.0f;
		randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 100 / 100.0f * randomNumber);
		pStars->Initialise(randomPosition);
		pObjectManager->AddObject(pStars);
	}
}

void HuntedLevelManager::Render()
{
	//Need todo this as displaying text the usual way using the Players Screen / Play Area no longer works
	//If player moves out of the original playing area as the camera follows the Player the text is no longer visible
	//moving the level manager with the player seemed to do nothing so having the text be releative to players position 
	//instead but doesn't look as good
	if (pThePlayer && pThePlayer->CheckIfActive() == true)
	{
		x = pThePlayer->GetPosition().XValue - 100;
		y = pThePlayer->GetPosition().YValue + 200;
		playerPos.set(x, y);
	}

	if (startingText)
	{
		//Displaying how long till Game starts
		MyDrawEngine::GetInstance()->WriteText(playerPos, L"Level starting in: ", MyDrawEngine::WHITE);
		//Displaying round timer
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(x + 360, y), (int)startingTextTimer, MyDrawEngine::WHITE);

		//Displaying some info which would normally be displayed to Player when they die
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playerPos.XValue, playerPos.YValue - 100),
												L"When you die return to Menu", MyDrawEngine::WHITE);

		//Start game 
		if (startingTextTimer <= 0.0f)
		{
			startGame = true;
			startingText = false;
		}
	}

	if (playerDead)
	{
		//The Player has died so displaying some final info
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 200,
												playingArea.GetTopLeft().YValue - 300), L"You Died, Time Survived: ",
												MyDrawEngine::RED);
		//Displaying round timer
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 380,
												playingArea.GetTopLeft().YValue - 300), (int)timeAlive, MyDrawEngine::RED);
	}
}

void HuntedLevelManager::Update(float frameTime)
{
	//If completed this would count how long the Player has been alive to display at the end
	timeAlive += frameTime;

	if (startingText)
		startingTextTimer -= frameTime;
	if (startGame)
		StartLevel();

	//As I would get issues with the Level Manager being passed to Player doing this instead
	//think its due to Circular Dependencies and I need a member variable for player in Level Manager so 
	//cant use the same method the Enemy Ship uses
	if (pThePlayer->CheckIfActive() == false)
	{
		PlayerDead();
	}
}

IShape2D& HuntedLevelManager::GetShape()
{
	return collisonShape;
}

void HuntedLevelManager::HandleCollision(GameObject& other) {}
void HuntedLevelManager::DrawCollision() {}

void HuntedLevelManager::StartLevel()
{
	//Turning to false as game has started and also stops lots of Enemies Spawning
	startGame = false;

	//Creating the 1st Enemy will create other Entities here if necessary
	EnemyShip* pEnemy = new EnemyShip();
	//Creating another random position
	Vector2D randomPosition;
	randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
	pEnemy->Initialise(pObjectManager, this, pThePlayer, Vector2D(0,0), pParticles);
	pObjectManager->AddObject(pEnemy);
}

void HuntedLevelManager::EnemyDead()
{
	//When a ship dies they will tell the Level Manager and a new one will be spawned
	EnemyShip* pEnemyShip = new EnemyShip();
	//Doing it again here will make every new spawned enemy have a different random location
	Vector2D randomPosition;
	randomPosition.setBearing(rand() % 628 / 100.0f, rand() % 500 + 500.0f);
	pEnemyShip->Initialise(pObjectManager, this, pThePlayer, randomPosition, pParticles);
	pObjectManager->AddObject(pEnemyShip);
}

void HuntedLevelManager::PlayerDead()
{
	//Player has Died so need to stop the game and display some text to the Player
	Game::instance.StopGame();
	playerDead = true;
}