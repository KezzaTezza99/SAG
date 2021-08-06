#include "SpaceInvadeEnemy.h"
#include "SpaceInvaderBullet.h"
#include "SpaceInvaderEnemyBullet.h"
#include "gamecode.h"
#include "Explosion.h"

const float BULLETSPEED = 600.0f;

SpaceInvadeEnemy::SpaceInvadeEnemy()
{
    this->pObjectManager = pObjectManager;
    this->pFormation = pFormation;
    this->offset = offset;
    this->pLevelManager = pLevelManager;
    position.set(0, 0);
    velocity.set(0, 0);
    randomShootDelay = rand() % 15 + 3.0f;      //3-15 Seconds Enemy Shoots
}

SpaceInvadeEnemy::~SpaceInvadeEnemy()
{
}

void SpaceInvadeEnemy::initialise(ObjectManager* pObjectManager, Vector2D offset, SpaceInvaderFormation* pFormation,
                                  SpaceInvaderLevelManager* pLevelManager)
{
    this->pObjectManager = pObjectManager;
    this->pFormation = pFormation;
    this->offset = offset;
    this->pLevelManager = pLevelManager;
    //Starting Position is defined in Level Manager. It allows me to space the enemies out in formation
    //-800 is to then bring that formation -900 on the x -> more to the left corner of the screen and not the centre
    //where they appear to begin with so cant have a lot of enemies before formation goes off the right
    //could probably clean this up and do it on viewport to suit all computer screens
    //position.set(startingPosition -900, 850);
    velocity.set(200, 0);
    LoadImage(L"enemy.bmp");        //Change This
    randomShootDelay = rand() % 15 + 3.0f;       //Going to have all enemies randomly shoot over a duration of time
    //Flipping the image 180 degrees to face correct way
    angle = float(3.142);
}

void SpaceInvadeEnemy::update(float frameTime)
{
    //If Level Manager is not Active delete self 
    //this will happen when Player dies for third time
    if (!pLevelManager->checkIfActive())
        Deactivate();

    //Movement
    position = pFormation->getPosition() + offset;
   
    //Shooting    
    if (randomShootDelay <= 0)
    {
        SpaceInvaderEnemyBullet* pBullet = new SpaceInvaderEnemyBullet();
        if (pBullet)
        {
            Vector2D vel;
            vel.setBearing(angle, BULLETSPEED);
            Vector2D offset;
            offset.setBearing(angle, 60.0f);
            pBullet->initialise(position + offset, velocity + vel);

            if (pObjectManager)
            {
                pObjectManager->addObject(pBullet);
                randomShootDelay = rand() % 15 + 3.0f;
            }
        }
    }
    //Adding a timer to count down before allowing us to shoot again
    randomShootDelay = randomShootDelay - frameTime;

    //Formation Movement
    //Getting Dimensions of Screen
    Rectangle2D playingArea = MyDrawEngine::GetInstance()->GetViewport();

    //If the Enemy hits right of screen we need to move them all left vice versa
    //Far right of screen
    if (position.XValue > playingArea.GetTopRight().XValue - 100)
    {
        //Enemy Moves Right
        pFormation->MoveDownRight();
    }
    //Left
    if (position.XValue < playingArea.GetTopLeft().XValue + 100)
    {
        //Enemy moves Left
        pFormation->MoveDownLeft();
    }  
}

IShape2D& SpaceInvadeEnemy::GetShape()
{
    collisionShape.PlaceAt(position, 50);
    return collisionShape;
}

void SpaceInvadeEnemy::HandleCollision(GameObject& other)
{
    if (typeid(other) == typeid(SpaceInvaderBullet))
    {
        //Creating Explosion
        Explosion* pExplosion = new Explosion();
        pExplosion->initialise(position);
        pObjectManager->addObject(pExplosion);

        //Deactivating the Enemy
        Deactivate();

        //Increasing Score
        pLevelManager->enemyDead();
    }
}

void SpaceInvadeEnemy::DrawCollision()
{
    MyDrawEngine::GetInstance()->FillCircle(collisionShape.GetCentre(), collisionShape.GetRadius(), MyDrawEngine::LIGHTGREEN);
    MyDrawEngine::GetInstance()->DrawLine(position, position + velocity, MyDrawEngine::RED);
}