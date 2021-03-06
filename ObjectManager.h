#pragma once
#include "GameObject.h"
#include <list>
#include <iostream>
class ObjectManager
{
private:
	std::list<GameObject*> pObjectList;

public:
	void addObject(GameObject* pGameObjects);
	void renderAll();
	void updateAll(float frameTime);
	void deleteAll();
	//void deleteInactiveObjects();
};

