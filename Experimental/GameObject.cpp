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
	imageSize = 1.0f;
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
	MyDrawEngine::GetInstance()->DrawAt(position, image, imageSize, angle);
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

void GameObject::SetImageSize(float size)
{
	imageSize = size;
}

float GameObject::GetImageSize() const
{
	return imageSize;
}

void GameObject::WrapScreen()
{
	//Wrapping the Player around the screen
	//Getting Dimensions of Screen
	Rectangle2D userScreen = MyDrawEngine::GetInstance()->GetViewport();

	//Up and Down
	if (position.YValue > userScreen.GetTopLeft().YValue + 40)			//Now off top of screen
	{
		//Setting position to be bottom of screen
		position.YValue = userScreen.GetBottomRight().YValue - 40;
	}
	if (position.YValue < userScreen.GetBottomRight().YValue - 40)		//Now off bottom of screen
	{
		//Setting position to be top of screen
		position.YValue = userScreen.GetTopLeft().YValue + 40;
	}
	//Left and Right
	if (position.XValue > userScreen.GetBottomRight().XValue + 40)
	{
		position.XValue = userScreen.GetTopLeft().XValue - 40;
	}
	if (position.XValue < userScreen.GetTopLeft().XValue - 40)
	{
		position.XValue = userScreen.GetBottomRight().XValue + 40;
	}
}





