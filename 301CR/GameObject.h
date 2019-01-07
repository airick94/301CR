#pragma once
#include "pch.h"
#include <iostream>
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "GameSettings.h"

class GameObject
{
protected:
	ObjectType type;
	sf::Sprite* sprite;
	b2Vec2 size;
	b2Vec2 position;

	b2Body* body;

	bool shouldRaycast = true;
	bool enabled = true;
public:
	GameObject();
	virtual ~GameObject();
	virtual ObjectType GetType();
	virtual void CreatePhysicsBody(GameObject & world);
	virtual void Update();
	virtual b2Body* GetBody();
	virtual sf::Sprite* GetSprite();
	virtual b2Vec2 GetPosition();
	virtual void SetPosition(b2Vec2 _position);
	virtual bool IsInBounds(sf::Vector2i _position);
	virtual void SetShouldRaycast(bool setTo);
	virtual bool IsEnabled();
};

