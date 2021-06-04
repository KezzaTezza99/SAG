#include "GameObject.h"
// TO-DO
//MAKE GAME OBJECTS TELL LEVEL MANAGER WE HAVE DIED TO STOP NULL POINTER WHEN WE DEAD
//MAKE COMPONENT SYSTEM
GameObject::GameObject()
{
	image = -1;		//There isnt an Image yet
	angle = 0;
	position.set(0, 0);
	isActive = true;
}

GameObject::~GameObject()
{

}

void GameObject::LoadImage(const wchar_t* filename)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

void GameObject::render()
{
	MyDrawEngine::GetInstance()->DrawAt(position, image, 1.0f, angle);
}

bool GameObject::checkIfActive() const
{
	return isActive;
}

void GameObject::DrawCollision()
{

}

Vector2D GameObject::getPosition()
{
	return Vector2D();
}





