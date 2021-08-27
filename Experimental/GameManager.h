//Author: w18024358
//Purpose: A level manager that is responsible for setting up the Arcade level and placing all three 
//"arcade" machines. The game manager is used at the start of the game and is deleted as soon as the Player chooses
//a Mini Game to play. 
//The final purpose of the Game Manager was to set up a "scene" for the player to interact with in the arcade 
//but this is currently not implemented
#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "ParticleSystem.h"

class GameManager : public GameObject
{
private:
	Circle2D collisionShape;
	ObjectManager* pObjectManager;
public:
	GameManager();
	void Initialise(ObjectManager* pObjectManager, ParticleSystem* pParticles);
	void Render() override;					
	void Update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};