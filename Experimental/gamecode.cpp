// GameCode.cpp		
// Modified by w18024358
//Added some code to display a different main menu than the default
//adds some visual effects 

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "GameManager.h"
#include "ParticleSystem.h"

Game::Game()
{
   // No-op
}

Game::~Game()
{
   // No-op
}

Game Game::instance;    // Singleton instance

// This is repeated, called every frame.
// It will run either Update( ), MainMenu() or PauseMenu() depending on the
// game state
ErrorType Game::Main()

{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err=SUCCESS;

	switch(m_currentState)
	{
	case MENU:

		err= MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // AsteroidPlayer has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err= Update();
		break;
   case GAMEOVER:
		err = FAILURE;       // Error return causes the window loop to exit
	default:
		// Not a valid state
		err = FAILURE;       // Error return causes the window loop to exit
	}

	return err;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}
}

// Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
// This is called soon after the program runs
ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}



// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
   // Any clean up code here 





	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}




// **********************************************************************************************
// Placeholder menus  ***************************************************************************
// **********************************************************************************************

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(450,220, L"Paused", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

   // Display menu options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

   // Get user input
	pInputs->SampleKeyboard();

   // Move choice up and down
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // If AsteroidPlayer chooses an option ....
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if(m_menuOption ==1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}

	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	//----------------------------------------------------------------------------------
	//Sorry Chris wanted to make a different Main Menu - how come if I create a a bunch of stars in a loop using a random
	//number they constantly move in a weird pattern? I suspect its due to random number's being seeded with system time?
	//and thus the new position keeps changing?

	//When the Player plays the Hunted game mode and moves out of the playing area as they can freeroam 
	//when they return to the main menu and replay the "Arcade" they no longer see anything as the camera is no longer
	//at the position (0,0) as needed
	//resetting the camera didn't seem todo anything so resetting and then replacing the Camera at the original position
	MyDrawEngine::GetInstance()->theCamera.Reset();
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(0, 0));			//Player no longer needs to quit to keep playing

	//Creating a Colour to use --- Dark Blue kinda colour / Space
	int r = 2;
	int g = 2;
	int b = 18;
	int colour = _XRGB(r, g, b);
	//Creating a rectangle that will be coloured to display over the entire screen
	Rectangle2D background = MyDrawEngine::GetInstance()->GetViewport();
	background.PlaceAt(background.GetBottomLeft(), background.GetTopRight());
	MyDrawEngine::GetInstance()->FillRect(background, colour);

	//Adding Image Assets around the Screen
	PictureIndex moon = MyDrawEngine::GetInstance()->LoadPicture(L"enc_moon.bmp");
	PictureIndex stars = MyDrawEngine::GetInstance()->LoadPicture(L"star.bmp");

	//Placing the Moon
	MyDrawEngine::GetInstance()->DrawAt(Vector2D(background.GetCentre().XValue + 980, 
										background.GetCentre().YValue + 250), moon, 3.0f);
	
	//As random numbers dont work going to use a mix of these to try and replicate the effect needed
	//very messy this way
	int spacing = 150;									//All will be spaced out on both Axis
	int variation = 40;									//Used to gradually add to both Axis again

	//Starting bottom left
	for (int i = 0; i < 6; i++)
	{
		//Placing the Stars
		MyDrawEngine::GetInstance()->DrawAt(Vector2D(background.GetBottomLeft().XValue + variation * i,
											background.GetBottomLeft().YValue + variation * i), stars, 1.0f);
		variation += 60;
	}

	//Starting bottom right
	for (int i = 0; i < 10; i++)
	{
		//Placing the Stars
		MyDrawEngine::GetInstance()->DrawAt(Vector2D(background.GetBottomRight().XValue - variation * i,
											background.GetBottomRight().YValue + 40 * i), stars, 1.0f);
		variation += 60;
	}

	variation = 40;										//Resetting back to 40
	//Starting top left
	for (int i = 0; i < 10; i++)
	{
		//Placing the Stars
		MyDrawEngine::GetInstance()->DrawAt(Vector2D(background.GetTopLeft().XValue + variation * i,
											background.GetTopLeft().YValue - variation * i), stars, 1.0f);
		variation += 80;
	}

	//Placing some Stars that are bigger
	MyDrawEngine::GetInstance()->DrawAt(Vector2D(200, 300), stars, 1.2f);
	MyDrawEngine::GetInstance()->DrawAt(Vector2D(700, -300), stars, 1.2f);
	//----------------------------------------------------------------------------------
	
	//Main Menu Text
	MyDrawEngine::GetInstance()->WriteText(450,220, L"Main menu", MyDrawEngine::WHITE);
	
	//Adding a message to display to Chris 
	//USING A DIFFERENT FONT SIZE
	MyDrawEngine::GetInstance()->WriteText(Vector2D(background.GetBottomRight().XValue - 750,
											background.GetBottomRight().YValue + 400),  L"Warning: Game in Alpha v0.3", 
											MyDrawEngine::RED, 1);							//Not actually Version 0.3 :D
	MyDrawEngine::GetInstance()->WriteText(Vector2D(background.GetBottomRight().XValue - 750,
											background.GetBottomRight().YValue + 300),	L"Hunted Game Mode Incomplete",
											MyDrawEngine::RED, 1);

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][15] = {L"Start game", L"Go Fullscreen",L"Exit"};

   // If the window is currently fullscreen, change the second option to read "Go Windowed" instead
	if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
	{
		wcscpy_s( options[1], 15, L"Go Windowed");
	}

   // Display the options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

   // Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // User selects an option
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)          // Play
		{  
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}

		if(m_menuOption ==1)          // Toggle full screen
		{
			if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
			{
				MyDrawEngine::GetInstance()->GoWindowed();
			}
			else
			{
				MyDrawEngine::GetInstance()->GoFullScreen();
			}
		}
		if(m_menuOption ==2)          //Quit
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}


// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************

// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to Initialise the core game
ErrorType Game::StartOfGame()
{
   // Code to set up your game *********************************************
   // **********************************************************************
	//Creating a Seed to Ensure Random Number Generation is always Random 
	srand(unsigned int(time(NULL)));				//If this isnt here random number will always produce the same value
	
	gt.mark();
	gt.mark();

	framesToFreeze = 0;								//Using this when the Player Dies and Respawns

	//Creating the Particles here and then giving it to the GameManager 
	//who can pass the particle system to all the necessary Level Managers
	ParticleSystem* pParticles = new ParticleSystem();
	pParticles->Initialise();
	objectManager.AddObject(pParticles);

	//Adding Game Manager which will start the Arcade Game and Level Manager
	//It will then be deleted, when the user choses a mini game the level manager will then be deleted.
	//Will create a new Level Manager based on the Mini Game
	GameManager* pGameManager = new GameManager();
	pGameManager->Initialise(&objectManager, pParticles);		
	objectManager.AddObject(pGameManager);

	return SUCCESS;
}

//Make level manager a super class and inherit on it based on what mini game will be played?
//Use game manager to start the arcade game but then delete it somehow when the mini game is chosen 
//game manager creates level manager based on mini game?

// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	// Check for entry to pause menu
	static bool escapepressed = true;
	if(KEYPRESSED(VK_ESCAPE))
	{
		if(!escapepressed)
			ChangeState(PAUSED);
		escapepressed=true;
	}
	else
		escapepressed=false;


   // Your code goes here *************************************************
   // *********************************************************************
   
	gt.mark();

	//Freezing Game
	if (framesToFreeze > 0)
	{
		gt.mdFrameTime = 0;
		framesToFreeze--;
	}

	objectManager.RenderAll();
	objectManager.UpdateAll(float(gt.mdFrameTime));
	objectManager.CheckAllCollisions();
	objectManager.DeleteInactiveObjects();

	/*ObjectManager objectFac;
	objectFac.RenderAll();
	objectFac.UpdateAll(float(gt.mdFrameTime));*/
	
   // *********************************************************************
   // *********************************************************************

	return SUCCESS;
}

// Called when the AsteroidPlayer ends the game
// Currently this is done from the PAUSED state, when returning to the main menu
// but could be done by the gameplay programmer in other situations
// This will be used by the gameplay programmer to clean up
ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
   // Add code here to tidy up ********************************************
   // *********************************************************************
	objectManager.DeleteAll();
	return SUCCESS;
}

void Game::FreezeGame()
{
	framesToFreeze = 50;
}

void Game::StopGame()
{
	//Stopping for long time this will happen when player dies and user needs to go back to Main Menu
	framesToFreeze = 5000;
}

