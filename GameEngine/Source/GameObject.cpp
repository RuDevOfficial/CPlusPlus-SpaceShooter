#include "Includes/GameObject.h"

void GameObject::Update(const float& dt) { }

void GameObject::OnCollision(GameObject* collidedObject)
{

}

void GameObject::SetPosition(int xPos, int yPos)
{
	Position->X = xPos;
	Position->Y = yPos;
}

GameObject::GameObject(char c, int xPos, int yPos)
{
	Letter = new char();
	Position = new Vector2(xPos, yPos);

	*Letter = c;
}

GameObject::~GameObject()
{
	delete Position;
	delete Letter;
}
