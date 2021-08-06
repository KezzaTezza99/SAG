//#include "EndGameMenu.h"
//#include "GameManager.h"
//
//EndGameMenu::EndGameMenu() 
//{
//	finalScore = 0;
//}
//
//EndGameMenu::~EndGameMenu() {}
//
//void EndGameMenu::render()
//{
//	//Displaying text telling the user they have died
//	MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
//		playingArea.GetCentre().YValue + 100), L"You Died", MyDrawEngine::RED);
//	
//	//Displaying the text "Score"
//	MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 180,
//		playingArea.GetCentre().YValue), L"Final Score: ", MyDrawEngine::RED);
//	
//	//Displaying the score
//	MyDrawEngine::GetInstance()->WriteInt(Vector2D(playingArea.GetCentre().XValue + 100,
//		playingArea.GetCentre().YValue), GetScore(), MyDrawEngine::RED);
//
//	//Displaying text to tell user to return to Main Menu
//	MyDrawEngine::GetInstance()->WriteText(Vector2D(playingArea.GetCentre().XValue - 460,
//		playingArea.GetCentre().YValue - 100), L"Please return to the Main Menu using ESC",
//		MyDrawEngine::RED);
//}
//
//void EndGameMenu::initialise(int finalScore)
//{
//	this->finalScore = finalScore;
//}
//
//void EndGameMenu::update(float frameTime)
//{
//}
//
//IShape2D& EndGameMenu::GetShape()
//{
//	collisonShape.PlaceAt(position, 10);
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
//int EndGameMenu::GetScore()
//{
//	return finalScore;
//}