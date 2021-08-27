//Author: w18024358
//Purpose: To manage the Space Invader Mini Game
#include "SpaceInvaderLevelManager.h"
#include "SpaceInvaderPlayer.h"
#include "SpaceInvadeEnemy.h"
#include "SpaceInvaderFormation.h"
#include "gamecode.h"
#include "Stars.h"

SpaceInvaderLevelManager::SpaceInvaderLevelManager()
{
	levelNumber = 0;								//Current level number
	numOfEnemies = 14;								//Number of enemies in a row
	this->pObjectManager = pObjectManager;			
	score = 0;										//Tracks score
	playerLives = 3;								//Number of lives the Player has
	//Player Ship loads the image to be used to display the Player's Lives Visually
	playerShip = MyDrawEngine::GetInstance()->LoadPicture(L"harrasser.bmp");		
	spacing = 200;									//Used to evenly space out the Enemy's in the Formation
	xPos = 0;										//Will over-ride this used too space Enemy's again 
	gameWon = false;								//Flag to display Game Won Text when the game is won
	invadersWon = false;							//Flag to display Game Over Text when the game is lost
	gameStartText = false;							//Used to display some text at the beginning off the game
													//using a flag to stop the Update function continuously counting down
	gameStartTimer = 5.0f;							//After 5 seconds Text will dissapear
}

void SpaceInvaderLevelManager::Initialise(ObjectManager* pObjectManager)
{
	levelNumber = 0;
	numOfEnemies = 14;
	this->pObjectManager = pObjectManager;
	int score = 0;
	playerLives = 3;
	playerShip = MyDrawEngine::GetInstance()->LoadPicture(L"harrasser.bmp");
	StartLevel();
	spacing = 200;
	xPos = 0;
	gameWon = false;
	invadersWon = false;
	gameStartText = false;
	gameStartTimer = 5.0f;
}

void SpaceInvaderLevelManager::StartLevel()
{
	//Enemies all need to know about Formation so creating here
	SpaceInvaderFormation* pFormation = new SpaceInvaderFormation();
	pFormation->Initialise();
	pObjectManager->AddObject(pFormation);

	levelNumber++;
	if (levelNumber == 1)
	{
		//Creating the Player
		SpaceInvaderPlayer* pPlayer = new SpaceInvaderPlayer();
		//Object Manager is needed to create bullers - Player needs level manager to track when player dies
		pPlayer->Initialise(&*pObjectManager, this, Vector2D(0, -850));
		pObjectManager->AddObject(pPlayer);
		
		//Creating the Enemies
		//Found an issue if there are to many enemies on the X the formation 
		//movement does not work as intended so maybe different screen sizes could break this
		//or behave differently than it should -- 14 works correctly for me if you have issues reduce and try again?
		for (int i = 0; i < numOfEnemies; i++)
		{
			//Stops Enemies being on top of each other
			xPos = i * spacing;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		//Creating stars for visual affect
		for (int i = 0; i < 20; i++)
		{
			Vector2D randomPosition;
			randomPosition.setBearing(rand() % 1000 / 100.0f, rand() % 500 + 500.0f);
			Stars* pStars = new Stars();
			pStars->Initialise(randomPosition);
			pObjectManager->AddObject(pStars);
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
			xPos = i * spacing;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 2; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 200);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}
	}

	//Level 3 will have 4 rows of enemies
	if (levelNumber == 3)
	{
		//If player has lost a life give one more
		if (playerLives < 3)
			playerLives++;

		numOfEnemies = 56;
		//When using nested loops for rows / columns I faced an issue of the next level starting when 14 enemies
		//killed or another issue with 28 enemies in each row so instead doing it a longer way
		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 200);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 400);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 4; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}
	}

	//Level 4 will have 5 rows of enemies and also give the Player one health
	if (levelNumber == 4)
	{
		numOfEnemies = 70;
		//If player has lost a life give one more
		if(playerLives < 3)
			playerLives++;
		
		for (int i = 0; i < numOfEnemies / 5; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 5; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 200);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 5; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 400);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 5; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 5; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}
	}

	//Level 5 will have 6 rows of enemies
	if (levelNumber == 5)
	{
		numOfEnemies = 84;

		for (int i = 0; i < numOfEnemies / 6; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 0);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 6; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 200);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 6; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 400);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 6; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 6; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}

		for (int i = 0; i < numOfEnemies / 6; i++)
		{
			xPos = i * spacing;
			offset.set(float(xPos), 600);

			SpaceInvadeEnemy* pEnemies = new SpaceInvadeEnemy();
			pEnemies->Initialise(&*pObjectManager, offset, &*pFormation, this);
			pObjectManager->AddObject(pEnemies);
		}
	}
}

void SpaceInvaderLevelManager::Update(float frameTime)
{
	if(gameStartText == false)
		gameStartTimer -= frameTime;				//Only counting down in the Beginning before set to True

	if (numOfEnemies <= 0)
	{
		if (levelNumber == 2)
			StartLevel();

		if (levelNumber == 3)
			StartLevel();
		
		if (levelNumber == 4)
			StartLevel();
		
		if (levelNumber == 5)
			StartLevel();
		
		if (levelNumber == 6)
			gameWon = true;
	}
}

void SpaceInvaderLevelManager::Render()
{
	if (gameStartText == false)
	{
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 350,
												playingArea.GetCentre().YValue), L"Dont't let the Invaders reach the line!",
												MyDrawEngine::WHITE);
		MyDrawEngine::GetInstance()->DrawLine(Vector2D(playingArea.GetBottomLeft().XValue,
												playingArea.GetCentre().YValue - 750), 
												Vector2D(playingArea.GetBottomRight().XValue,
												playingArea.GetCentre().YValue - 750), MyDrawEngine::RED);
		if (gameStartTimer <= 0.0f)
			gameStartText = true;
	}
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
		MyDrawEngine::GetInstance()->ClearBackBuffer();

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
												playingArea.GetCentre().YValue - 100), 
												L"Please return to the Main Menu using ESC", MyDrawEngine::RED);
	}

	//Happens when Player wins the game
	if (gameWon)
	{
		MyDrawEngine::GetInstance()->ClearBackBuffer();

		//Displaying text telling the user they have won
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue + 100), L"You Won!", MyDrawEngine::GREEN);

		//Displaying the text "Score"
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue), L"Final Score: ", MyDrawEngine::GREEN);

		//Displaying the score
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100,
												playingArea.GetCentre().YValue), score, MyDrawEngine::GREEN);

		//Displaying text to tell user to return to Main Menu
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 460,
												playingArea.GetCentre().YValue - 100), 
												L"Please return to the Main Menu using ESC", MyDrawEngine::GREEN);
	}

	//Happens when Space Invaders reach the bottom of screen and win the game
	if (invadersWon)
	{
		int playerLivesRemaining = 3 - playerLives;

		//Clearing the screen
		MyDrawEngine::GetInstance()->ClearBackBuffer();

		//Displaying text telling the user they have lost
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue + 100), L"You Lost!", MyDrawEngine::RED);

		//Displaying the text "Score"
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue), L"Final Score: ", MyDrawEngine::RED);

		//Displaying the score
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100,
												playingArea.GetCentre().YValue), score, MyDrawEngine::RED);

		//Displaying how much lives the Player had lost
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
												playingArea.GetCentre().YValue - 100), L"Lives Lost: ", MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100,
												playingArea.GetCentre().YValue - 100), playerLivesRemaining,
												MyDrawEngine::RED);

		//Displaying text to tell user to return to Main Menu
		MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 460,
												playingArea.GetCentre().YValue - 200), 
												L"Please return to the Main Menu using ESC", MyDrawEngine::RED);
	}
}

IShape2D& SpaceInvaderLevelManager::GetShape()
{
	return collisionShape;
}

void SpaceInvaderLevelManager::HandleCollision(GameObject& other) {}
void SpaceInvaderLevelManager::DrawCollision() {}

void SpaceInvaderLevelManager::EnemyDead()
{
	score += 10;
	numOfEnemies--;

	if (numOfEnemies == 0)
		StartLevel();
}

void SpaceInvaderLevelManager::PlayerDead()
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

	//If lives are not 0 then the game is over because the formation has reached the bottom 
	if (playerLives != 0)
		invadersWon = true;
}

void SpaceInvaderLevelManager::Respawn()
{
	//Briefly freezing the game before allowing the Player to keep Playing
	Game::instance.FreezeGame();

	//Creating a new Player 
	if (playerLives != 0 || playerLives <= 0)
	{
		SpaceInvaderPlayer* pPlayer = new SpaceInvaderPlayer();
		pPlayer->Initialise(&*pObjectManager, this, lastPosition);
		pObjectManager->AddObject(pPlayer);
	}
}

void SpaceInvaderLevelManager::GetPlayerPosition(Vector2D lastPos)
{
	this->lastPosition = lastPos;
}