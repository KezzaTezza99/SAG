//Author: w18024358
//Purpose: To manage all the Game Objects in the Game such as rendering, deleting, updating 
//collisions etc
#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{
private:
	std::list<GameObject*> pObjectList;				//Stores a list of pointers pointing to Game Objects

public:
	~ObjectManager();								//When the Destructor is called it will also delete the Game Objects
	void AddObject(GameObject* pGameObjects);		//Adds a Game Object to the List
	void RenderAll();								//Renders all Game Objects
	void UpdateAll(float frameTime);				//Update's all Game Objects
	void DeleteAll();								//Deletes all Game Objects called in Destructor
	void DeleteInactiveObjects();					//Deletes any inactive Game Objects
	void CheckAllCollisions();						//Checks all collisions
};