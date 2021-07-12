#include "ObjectManager.h"
#include "Player.h"
#include "Rock.h"
#include "Bullet.h"
#include "Stars.h"
#include "EnemyShip.h"
#include "myinputs.h"

ObjectManager::~ObjectManager()
{
	deleteAll();
}

void ObjectManager::addObject(GameObject* pGameObjects)
{
	pObjectList.push_back(pGameObjects);
}

void ObjectManager::renderAll()
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		if(pNextGameObject && pNextGameObject->checkIfActive())
		{
			pNextGameObject->render();
			MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(), MyDrawEngine::GREEN);
		}
	}

	//Show Collisions when Pressing H button
	MyInputs::GetInstance()->SampleKeyboard();
	if (MyInputs::GetInstance()->KeyPressed(DIK_H))
	{
		for (GameObject* pNextGameObject : pObjectList)
		{
			if (pNextGameObject && pNextGameObject->checkIfActive())
			{
				pNextGameObject->DrawCollision();
			}
		}
	}

}

void ObjectManager::updateAll(float frameTime)
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		if(pNextGameObject && pNextGameObject->checkIfActive())
		{
			pNextGameObject->update(frameTime);
		}
	}
}

void ObjectManager::deleteAll()
{
	for(GameObject* pNextGameObject : pObjectList)
	{
		delete pNextGameObject;
		pNextGameObject = nullptr;
	}
	pObjectList.clear();
}

void ObjectManager::deleteInactiveObjects()
{
	for (GameObject* &pNextGameObject : pObjectList)
	{
		if(pNextGameObject && !pNextGameObject->checkIfActive())
		{
			delete pNextGameObject;
			pNextGameObject = nullptr;
		}
	}
	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);		//Putting all of the Nullptrs to end of the list
	pObjectList.erase(it, pObjectList.end());	//Removing everything at the end of the List - all the nullptrs 
}

void ObjectManager::checkAllCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		for (it2 = next(it1); it2 != pObjectList.end(); it2++)
		{
			if ((*it1) && (*it2) &&
				(*it1)->checkIfActive() && (*it2)->checkIfActive() &&
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
	
	if (name == L"player")
	{
		pNewObject = new Player();
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
		addObject(pNewObject);
	}
	
	return pNewObject;
}
*/