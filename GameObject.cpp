#include "GameObject.h"

GameObject::GameObject()
{
	image = -1;		//There isnt an Image yet
	angle = 0;
	position.set(0, 0);
	isActive = true;
}

void GameObject::LoadImage(const wchar_t* filename)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

void GameObject::render()
{
	/*if(isActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, image, 1.0f, angle);
	}*/

	MyDrawEngine::GetInstance()->DrawAt(position, image, 1.0f, angle);
}

bool GameObject::checkIfActive() const
{
	return isActive;
}



