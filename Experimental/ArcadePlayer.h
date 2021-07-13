#pragma once
#include "GameObject.h"
#include "GameManager.h"

class ArcadePlayer : public GameObject
{
private:
	Circle2D collisionShape;
	Vector2D velocity;
	Vector2D acceleration;
	GameManager* pGameManager;		//Used to Delete Level Manager / Game Manager on Mini Game Start Up
public:
	ArcadePlayer();
	~ArcadePlayer();
	void initialise(GameManager* pGameManager);
	void update(float frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void DrawCollision();
	void Deactivate();
};