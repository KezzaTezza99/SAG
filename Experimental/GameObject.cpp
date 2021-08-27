//Author: w18024358
//Purpose: Implement code to allow for 
#include "GameObject.h"

GameObject::GameObject()
{
	image = -1;										//There isnt an Image yet
	angle = 0;										//Angle should be 0 to begin
	position.set(0, 0);								
	isActive = true;								//Every Game Object will be Active to begin
	imageSize = 1.0f;								//Defualt size of Game Object Bitmaps 

	//Getting Dimensions of Screen to be used for a few reasons
	//Wrapping screen and keep text etc in same location no matter on the users' screen
	playingArea = MyDrawEngine::GetInstance()->GetViewport();
}

GameObject::~GameObject() {}

void GameObject::LoadImage(const wchar_t* filename)
{
	//Loading the Bitmap with the filename param that is passed
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

void GameObject::Render()
{
	//Drawing the Game Object
	MyDrawEngine::GetInstance()->DrawAt(position, image, imageSize, angle);
}

bool GameObject::CheckIfActive() const
{
	//Used to check if active as some operations will need this information
	return isActive;
}

//Used for Debugging 
void GameObject::DrawCollision() {}

//Useful for some functionallity 
Vector2D GameObject::GetPosition()
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
	//Wrapping the screen
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