#include "SpaceInvaderLevelManager.h"
#include "SpaceInvaderPlayer.h"
#include "SpaceInvadeEnemy.h"
#include "SpaceInvaderFormation.h"
#include "myinputs.h"
#include "gamecode.h"

SpaceInvaderLevelManager::SpaceInvaderLevelManager()
{
	levelNumber = 0;
	numOfEnemies = 14;
	this->pObjectManager = pObjectManager;
	score = 0;
	playerLives = 3;
	playerShip = MyDrawEngine::GetInstance()->LoadPicture(L"harrasser.bmp");
}

SpaceInvaderLevelManager::~SpaceInvaderLevelManager()
{
}

void SpaceInvaderLevelManager::initialise(ObjectManager* pObjectManager)
{
	levelNumber = 0;
	numOfEnemies = 14;
	this->pObjectManager = pObjectManager;
	int score = 0;
	playerLives = 3;
	playerShip = MyDrawEngine::GetInstance()->LoadPicture(L"harrasser.bmp");
	startLevel();
}

void SpaceInvaderLevelManager::startLevel()
{
	//Enemies all need to know about Formation so creating here
	SpaceInvaderFormation* pFormation = new SpaceInvaderFormation();
	pFormation->initialise();
	pObjectManager->addObject(pFormation);

	levelNumber++;
	if (levelNumber == 1)
	{
		//Creating the Player
		SpaceInvaderPlayer* pPlayer = new SpaceInvaderPlayer();
		//Object Manager is needed to create bullers - Player needs level manager to track when player dies
		pPlayer->initialise(&*pObjectManager, this);
		pObjectManager->addObject(pPlayer);

		//Creating the Enemies
		//Found an issue if there are to many enemies on the X the formation 
		//movement does not work as intended so maybe different screen sizes could break this
		//or behave differently than it should
		for (int i = 0; i < numOfEnemies; i++)
		{
			//Stops Enemies being on top of each other
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}
	}

	////Level 2 will have two rows of enemies
	//if (levelNumber == 2)
	//{
	//	for (int row = 0; row < 2; row++)
	//	{
	//		for (int i = 0; i < numOfEnemies; i++)
	//		{
	//			//Stops Enemies being on top of each other
	//			int spacing = 200;
	//			int xPos = i * spacing;
	//			Vector2D offset;
	//			offset.set(xPos, row * spacing);

	//			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
	//			pEnemies->initialise(&*pObjectManager, offset, &*pFormation);
	//			pObjectManager->addObject(pEnemies);
	//		}
	//	}
	//}

	////Level 3 will have three rows of enemies
	//if (levelNumber == 3)
	//{
	//	for (int i = 0; i < numOfEnemies; i++)
	//	{
	//		for (int row = 1; row < 3; row++)
	//		{
	//			//Stops Enemies being on top of each other
	//			int spacing = 200;
	//			int xPos = i * spacing;
	//			offset.set(i * spacing, row * spacing);
	//		}
	//		SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
	//		pEnemies->initialise(&*pObjectManager, offset, &*pFormation);
	//		pObjectManager->addObject(pEnemies);
	//	}
	//}
}

void SpaceInvaderLevelManager::update(float frameTime)
{
	if (numOfEnemies <= 0)
	{
		//Could add a timer of say 5 seconds before each level starts
		//would then do if(timer <=0) {start}
		if (levelNumber == 2)
		{
			startLevel();
		}

		if (levelNumber == 3)
		{
		}
	}
}

void SpaceInvaderLevelManager::render()
{
	//Far Left
	//Using playing area to ensure text is always in same location for all screen types and users
	//Displaying the text "level"
	MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetTopLeft().XValue + 50, 
								playingArea.GetTopLeft().YValue - 20), (L"Level: "), MyDrawEngine::GREEN);
   
	//Displying the level number 
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetTopLeft().XValue + 200,
								playingArea.GetTopLeft().YValue - 20), levelNumber, MyDrawEngine::GREEN);
	
	//Centre ish 
	//Displaying the text "score"
	MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
								playingArea.GetTopLeft().YValue - 20), (L"Score: "), MyDrawEngine::GREEN);
	
	//Displaying the score
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue,
								playingArea.GetTopLeft().YValue - 20), score, MyDrawEngine::GREEN);

	//Far Right
	//Displaying the text "Lives" -- Need a higher number as text is wrote left to right and goes off screen
	MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetTopRight().XValue - 500,
								playingArea.GetTopRight().YValue - 20), (L"Lives: "), MyDrawEngine::GREEN);

	//Drawing the number of player lives and the image of the player
	for (int i = 0; i < playerLives; i++)
	{
		MyDrawEngine::GetInstance()->DrawAt(Vector2D(playingArea.GetTopRight().XValue - 100 - 100 * i,
								playingArea.GetTopRight().YValue - 50), playerShip, 0.3f);
	}
}

IShape2D& SpaceInvaderLevelManager::GetShape()
{
	return collisionShape;
}

void SpaceInvaderLevelManager::HandleCollision(GameObject& other)
{
}

void SpaceInvaderLevelManager::DrawCollision() { DisplayScore(); }

void SpaceInvaderLevelManager::enemyDead()
{
	score += 10;
	numOfEnemies--;
}

void SpaceInvaderLevelManager::playerDead()
{
	//GameOver();
}

void SpaceInvaderLevelManager::GameOver()
{
	MyDrawEngine::GetInstance()->ClearBackBuffer();
	Game::instance.MainMenu();
}

int SpaceInvaderLevelManager::GetScore() const
{
	return score;
}


void SpaceInvaderLevelManager::DisplayScore()
{
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(0, 0), GetScore(), MyDrawEngine::WHITE);
}