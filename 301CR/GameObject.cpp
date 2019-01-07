#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

ObjectType GameObject::GetType()
{
	return type;
}

void GameObject::CreatePhysicsBody(GameObject & world)
{
}

void GameObject::Update()
{
}

b2Body * GameObject::GetBody()
{
	return body;
}

sf::Sprite * GameObject::GetSprite()
{
	return sprite;
}

b2Vec2 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(b2Vec2 _position)
{
	position = _position;
}

bool GameObject::IsInBounds(sf::Vector2i _position)
{
	if(shouldRaycast)
	{
		float currentPosX = position.x * SETTINGS_SCALE;
		float currentPosY = position.y * SETTINGS_SCALE;
		float sizeX = size.x * SETTINGS_SCALE;
		float sizeY = size.y * SETTINGS_SCALE;

		if (_position.x <= currentPosX + sizeX / 2 && _position.y >= currentPosY - sizeY / 2 &&
			_position.x >= currentPosX - sizeX / 2 && _position.y <= currentPosY + sizeY / 2)
		{
			std::cout << "HIT" << std::endl;
			return true;
		}
	}
	
	return false;
}

void GameObject::SetShouldRaycast(bool setTo)
{
	shouldRaycast = setTo;
}

bool GameObject::IsEnabled()
{
	return enabled;
}

