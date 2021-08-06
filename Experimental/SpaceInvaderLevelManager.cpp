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

SpaceInvaderLevelManager::~SpaceInvaderLevelManager() {}

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
		pPlayer->initialise(&*pObjectManager, this, Vector2D(0, -850));
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

	//Level 2 will have two rows of enemies
	if (levelNumber == 2)
	{
		numOfEnemies = 28;
		//When using nested loops for rows / columns I faced an issue of the next level starting when 14 enemies
		//killed or another issue with 28 enemies in each row so instead doing it a longer way
		//Will come back and try fixing but I know this works and have time constraints 
		for (int i = 0; i < numOfEnemies / 2; i++)
		{
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 2; i++)
		{
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 200);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}
	}

	//Level 3 will have 4 rows of enemies
	if (levelNumber == 3)
	{
		numOfEnemies = 56;
		//When using nested loops for rows / columns I faced an issue of the next level starting when 14 enemies
		//killed or another issue with 28 enemies in each row so instead doing it a longer way
		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 200);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 400);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			int spacing = 200;
			int xPos = i * spacing;
			Vector2D offset;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->addObject(pEnemies);
		}
	}
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
			startLevel();
		}

		if (levelNumber == 4)
		{
			startLevel();
		}

		if (levelNumber == 5)
		{
			startLevel();
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

	//Happens when Player is Dead
	if (playerLives == 0)
	{
		//Displaying text telling the user they have died
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
			playingArea.GetCentre().YValue + 100), L"You Died", MyDrawEngine::RED);

		//Displaying the text "Score"
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
			playingArea.GetCentre().YValue), L"Final Score: ", MyDrawEngine::RED);

		//Displaying the score
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100,
			playingArea.GetCentre().YValue), score, MyDrawEngine::RED);

		//Displaying text to tell user to return to Main Menu
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 460,
			playingArea.GetCentre().YValue - 100), L"Please return to the Main Menu using ESC",
			MyDrawEngine::RED);
	}
}

IShape2D& SpaceInvaderLevelManager::GetShape()
{
	return collisionShape;
}

void SpaceInvaderLevelManager::HandleCollision(GameObject& other) {}

void SpaceInvaderLevelManager::DrawCollision() {}

void SpaceInvaderLevelManager::enemyDead()
{
	score += 10;
	numOfEnemies--;

	if (numOfEnemies == 0)
		startLevel();
}

void SpaceInvaderLevelManager::playerDead()
{
	//Remove one life and then re-add the player back into the Game
	playerLives--;

	if(playerLives != 0)
		Respawn();

	else if (playerLives == 0)
		GameOver();
	
	if (playerLives < 0)
		playerLives = 0;
}

void SpaceInvaderLevelManager::GameOver()
{
	//Stopping the Game
	Game::instance.StopGame();
}

void SpaceInvaderLevelManager::Respawn()
{
	//Briefly freezing the game before allowing the Player to keep Playing
	Game::instance.FreezeGame();

	//Creating a new Player 
	if (playerLives != 0 || playerLives <= 0)
	{
		SpaceInvaderPlayer* pPlayer = new SpaceInvaderPlayer();
		pPlayer->initialise(&*pObjectManager, this, lastPosition);
		pObjectManager->addObject(pPlayer);
	}
}

Vector2D SpaceInvaderLevelManager::GetPlayerPosition(Vector2D lastPosition)
{
	this->lastPosition = lastPosition;
	return lastPosition;
}
