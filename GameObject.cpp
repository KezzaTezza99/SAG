#include "GameObject.h"

GameObject::GameObject()
{
	image = -1;		//There isnt an Image yet
	angle = 0;
	position.set(0, 0);
	isActive = false;
}

void GameObject::LoadImage(const wchar_t* filename)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

void GameObject::render()
{
	MyDrawEngine::GetInstance()->DrawAt(position, image, 1.0f, angle);
}



