//Author: w18024358
//Purpose: The purpose of this class is to create Particles to enhance the game, the main use right now is for 
//better Explosions and they class has only been implemented into Hunted Player
//The Particle system will be implemented into the rest of the Game once I have updated
//to a component system
#pragma once
#include "GameObject.h"

// TODO ------------------------------------------------------------------
//When updating from Flat to Component System can easily update the class 
//------------------------------------------------------------------------
class ParticleSystem : public GameObject
{
	static const int MAX = 200;						//Max amount of Particles allowed in Game
private:
	Vector2D positions[MAX];						//Store's an Array off Positions for each Particle
	Vector2D velocities[MAX];						//Store's all the Velocities in an Array for each Particle
	unsigned int colours[MAX];						//Store's a single colour for each individual Particle
	Point2D collisionShape;							//Necessary even though no Collisions due to Engine Architecture
	int next;										//Used for adding Particles to the Array's
public:
	ParticleSystem();
	void Initialise();
	void Update(float frameTime);
	void Render() override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void AddSingleParticles(Vector2D startPosition, Vector2D startVelocity, unsigned int colour);
	void AddParticles(Vector2D startPosition, float maxVelocity, unsigned int colour, int numOfParticles);
};

