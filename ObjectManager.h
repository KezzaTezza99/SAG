#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{
private:
	std::list<GameObject*> pObjectList;

public:
	~ObjectManager();
	void addObject(GameObject* pGameObjects);
	void renderAll();
	void updateAll(float frameTime);
	void deleteAll();
	void deleteInactiveObjects();
	void checkAllCollisions();

	//Turning the Object Manager into Object Factory
	//GameObject* add(std::wstring name);
	//GameObject* addObjectToFactory(std::wstring name, GameObject*());
};

