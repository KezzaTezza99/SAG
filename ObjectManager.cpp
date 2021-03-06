#include "ObjectManager.h"

void ObjectManager::addObject(GameObject* pGameObjects)
{
	pObjectList.push_back(pGameObjects);
}

void ObjectManager::renderAll()
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		if(pNextGameObject->checkIfActive())
		{
			pNextGameObject->render();
		}
	}
	MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(), MyDrawEngine::GREEN);
}

void ObjectManager::updateAll(float frameTime)
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		if(pNextGameObject->checkIfActive())
		{
			pNextGameObject->update(frameTime);
		}
	}
}

void ObjectManager::deleteAll()
{
	for (GameObject* pNextGameObject : pObjectList)
	{
		delete pNextGameObject;
		pNextGameObject = nullptr;
	}
	pObjectList.clear();
}

//void ObjectManager::deleteInactiveObjects()
//{
//	for (GameObject* pNextGameObject : pObjectList)
//	{
//		
//		if (!pNextGameObject->checkIfActive())
//		{
//			delete pNextGameObject;
//			pNextGameObject = nullptr;
//
//			//Throws Exceptions and Crashes Program if Nullptrs left in the list
//			//This removes all nullptrs 
//			auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);		//Putting all of the Nullptrs to end of the list
//			pObjectList.erase(it, pObjectList.end());	//Removing everything at the end of the List - all the nullptrs 
//		}
//	}
//}

