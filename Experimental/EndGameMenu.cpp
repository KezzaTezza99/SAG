//#include "EndGameMenu.h"
//#include "GameManager.h"
//
//Come back and fix this one day casuing issues and not sure why
//EndGameMenu::EndGameMenu()
//{
//	currentSelection = 0;
//}
//
//EndGameMenu::~EndGameMenu()
//{
//}
//
//void EndGameMenu::render()
//{
//	
//}
//
//void EndGameMenu::initialise(ObjectManager* pObjectManager)
//{
//	currentSelection = 0;
//}
//
//void EndGameMenu::update(float frameTime)
//{
//	Menu();
//}
//
//IShape2D& EndGameMenu::GetShape()
//{
//	return collisonShape;
//}
//
//void EndGameMenu::HandleCollision(GameObject& other)
//{
//}
//
//void EndGameMenu::DrawCollision()
//{
//}
//
//void EndGameMenu::Menu()
//{
//	MyDrawEngine::GetInstance()->WriteText(450, 220, L"High Score", MyDrawEngine::WHITE);
//	const int PLAYERCHOICE = 4;
//	wchar_t userOptions[PLAYERCHOICE][12] = { L"Arcade Mode", L"Replay", L"Main Menu", L"Exit" };
//
//	//Displaying the Options to the User
//	for (int i = 0; i < PLAYERCHOICE; i++)
//	{
//		int colour = MyDrawEngine::GREY;
//		
//		if (i == currentSelection)
//		{
//			colour = MyDrawEngine::WHITE;
//		}
//		MyDrawEngine::GetInstance()->WriteText(450, 300 + 50 * i, userOptions[i], colour);
//	}
//
//	//Getting the Input from the Player
//	MyInputs* pInputs = MyInputs::GetInstance();
//	pInputs->SampleKeyboard();
//
//	//Navigating the Menu
//	if (pInputs->NewKeyPressed(DIK_UPARROW))
//	{
//		currentSelection--;
//	}
//	if (pInputs->NewKeyPressed(DIK_W))
//	{
//		currentSelection++;
//	}
//	if (currentSelection < 0)
//	{
//		currentSelection = 0;
//	}
//	else if (currentSelection >= PLAYERCHOICE)
//	{
//		currentSelection = PLAYERCHOICE - 1;
//	}
//
//	//Logic for when user selects and option
//	if (pInputs->NewKeyPressed(DIK_E))
//	{
//		if (currentSelection == 0)			//Return to Arcade Mode
//		{
//			
//		}
//
//		if (currentSelection == 1)         //Replay Mini Game
//		{
//
//		}
//
//		if (currentSelection == 2)         //Main Menu
//		{
//
//		}
//
//		if (currentSelection == 3)			//Exit
//		{
//
//		}
//	}
//}