//Author: w18024358
//Purpose: To create a list of Game Objects that can provide an easy way to 
//render, update, delete and collision detection for all objects in the game
#include "ObjectManager.h"
#include "myinputs.h"

ObjectManager::~ObjectManager()
{
	//When the Object Manager has been Destroyed call this method
	DeleteAll();									//Delete's all Game Objects in the List
}

void ObjectManager::AddObject(GameObject* pGameObjects)
{
	pObjectList.push_back(pGameObjects);			//Adding a Game Object to the List
}

void ObjectManager::RenderAll()
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		if(pNextGameObject && pNextGameObject->CheckIfActive())
		{
			//For evert Active Game Object in the List then Render the Game Object
			pNextGameObject->Render();
		}
	}

	//Getting keyboard input
	MyInputs::GetInstance()->SampleKeyboard();
	//Gets useful debug infromation such as Collision Shapes and Object Manager list size - When "H" is pressed
	if (MyInputs::GetInstance()->KeyPressed(DIK_H))
	{
		for (GameObject* pNextGameObject : pObjectList)
		{
			//For every active object in the list
			if (pNextGameObject && pNextGameObject->CheckIfActive())
			{
				//Draw Collision Shapes
				pNextGameObject->DrawCollision();
				//Debug Info - Not using PlayingArea to place text in same location due to being a game object variable
				MyDrawEngine::GetInstance()->WriteText(5, 50, L"Object's in List: ", MyDrawEngine::GREEN);
				MyDrawEngine::GetInstance()->WriteInt(145, 50, pObjectList.size(), MyDrawEngine::GREEN);
			}
		}
	}
}

void ObjectManager::UpdateAll(float frameTime)
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		if(pNextGameObject && pNextGameObject->CheckIfActive())
		{
			//All active objects in the list will be updated
			pNextGameObject->Update(frameTime);
		}
	}
}

void ObjectManager::DeleteAll()
{
	//Deleting all the pointers in list and setting to nullptr before clearing the list
	for(GameObject* pNextGameObject : pObjectList)
	{
		delete pNextGameObject;
		pNextGameObject = nullptr;
	}
	pObjectList.clear();
}

void ObjectManager::DeleteInactiveObjects()
{
	for (GameObject* &pNextGameObject : pObjectList)
	{
		if(pNextGameObject && !pNextGameObject->CheckIfActive())
		{
			delete pNextGameObject;
			pNextGameObject = nullptr;
		}
	}
	//Putting all of the Nullptrs to end of the list
	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);		
	//Removing everything at the end of the List - all the nullptrs 
	pObjectList.erase(it, pObjectList.end());										
}

void ObjectManager::CheckAllCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		for (it2 = next(it1); it2 != pObjectList.end(); it2++)
		{
			if ((*it1) && (*it2) &&
				(*it1)->CheckIfActive() && (*it2)->CheckIfActive() &&
				(*it1)->GetShape().Intersects((*it2)->GetShape()))
			{
				(*it1)->HandleCollision(**it2);
				(*it2)->HandleCollision(**it1);
			}
		}
	}
}

/*
GameObject* ObjectManager::addObjectToFactory(std::wstring name)
{
	GameObject* pNewObject = nullptr;
	
	if (name == L"AsteroidPlayer")
	{
		pNewObject = new AsteroidPlayer();
	}
	else if (name == L"asteroid")
	{
		pNewObject = new Rock();
	}
	else if (name == L"bullet")
	{
		pNewObject = new Bullet();
	}
	else if (name == L"star")
	{
		pNewObject = new Stars();
	}
	else if (name == L"enemyship")
	{
		pNewObject == new EnemyShip();
	}
	else
	{
		ErrorLogger::Write(L"Could not create item: ");
		ErrorLogger::Writeln(name.c_str());
	}
	
	//If the Pointer to object exists send it to add object
	if (pNewObject)
	{
		AddObject(pNewObject);
	}
	
	return pNewObject;
}
*/