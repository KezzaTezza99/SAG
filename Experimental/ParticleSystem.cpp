//Author: w18024358
//Purpose: Add some visual effects to make the Explosions feel better
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
    for (int i = 0; i < MAX; i++)
    {
        positions[i].set(-50000.0f, -50000.0f);     //Placing particles very far away
        velocities[i].set(-50000.0f, -50000.0f);
        colours[i] = MyDrawEngine::RED;             //Doing this to stop the warning I would get
    }
    next = 0;                                       
    collisionShape.PlaceAt(Vector2D(-50000.0f, -50000.0f));
    isActive = true;
}

void ParticleSystem::Initialise()
{
    //Doing this for the Asteroids and Space Invaders Mini Game is fine
    //player will never actually be able to find and see the particles 
    //but for the Hunted Mini Game there can be a slight chance that the player
    //gets to the position and sees the particles
    //could try and develop a different methods if this proves to be an issue
    for (int i = 0; i < MAX; i++)
    {
        positions[i].set(-50000.0f, -50000.0f);
        velocities[i].set(-50000.0f, -50000.0f);
    }
    next = 0;
    collisionShape.PlaceAt(Vector2D(-50000.0f, -50000.0f));
    isActive = true;
}

void ParticleSystem::Update(float frameTime)
{
    for (int i = 0; i < MAX; i++)
    {
        positions[i] += velocities[i] * frameTime; 
    }
}

void ParticleSystem::Render() 
{
    MyDrawEngine::GetInstance()->DrawPointList(positions, colours, MAX);
}

IShape2D& ParticleSystem::GetShape()
{
    return collisionShape;
}

void ParticleSystem::HandleCollision(GameObject& other)
{
    ////Does not work currently come back and fix --- Collision Shape a Circle instead of Point?
    ////Particles will Bounce off the Player and Enemy Ship
    //if (typeid(other) == typeid(HuntedPlayer) || typeid(other) == typeid(EnemyShip))
    //{
    //    Vector2D normal = (position - other.GetPosition()).unitVector();
    //    for (int i = 0; i < MAX; i++)
    //    {
    //        Vector2D velocity = velocities[i];
    //        if (normal * velocity < 0)
    //        {
    //            velocity = velocity - 2 * (velocity * normal) * normal;
    //            velocity = velocity * 1.5f;
    //        }
    //    }
    //}
}

void ParticleSystem::AddSingleParticles(Vector2D startPosition, Vector2D startVelocity, unsigned int colour)
{
    positions[next] = startPosition;
    velocities[next] = startVelocity;
    colours[next] = colour;
    next++;

    if (next >= MAX)
    {
        next = 0;
    }
}

void ParticleSystem::AddParticles(Vector2D startPosition, float maxVelocity, unsigned int colour, int numOfParticles)
{
    for (int i = 0; i < numOfParticles; i++)
    {
        Vector2D velocity;
        velocity.setBearing(rand() % 628 / 100.0f, rand() % 100 / 100.0f * maxVelocity);
        AddSingleParticles(startPosition, velocity, colour);
    }
}