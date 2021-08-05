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

	//Getting Dimensions of Screen to be used for a few reasons
	//Wrapping screen and keep text etc in same location no matter on the users' screen
	playingArea = MyDrawEngine::GetInstance()->GetViewport();
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

void GameObject::DrawCollision() {}

Vector2D GameObject::getPosition()
{
	return position;
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
	//Wrapping the AsteroidPlayer around the screen

	//Up and Down
	if (position.YValue > playingArea.GetTopLeft().YValue + 40)			//Now off top of screen
	{
		//Setting position to be bottom of screen
		position.YValue = playingArea.GetBottomRight().YValue - 40;
	}
	if (position.YValue < playingArea.GetBottomRight().YValue - 40)		//Now off bottom of screen
	{
		//Setting position to be top of screen
		position.YValue = playingArea.GetTopLeft().YValue + 40;
	}
	//Left and Right
	if (position.XValue > playingArea.GetBottomRight().XValue + 40)
	{
		position.XValue = playingArea.GetTopLeft().XValue - 40;
	}
	if (position.XValue < playingArea.GetTopLeft().XValue - 40)
	{
		position.XValue = playingArea.GetBottomRight().XValue + 40;
	}
}

void GameObject::Deactivate()
{
	isActive = false;
}







