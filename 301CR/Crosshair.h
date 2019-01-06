#pragma once

#include "pch.h"
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "GameSettings.h"

class Crosshair
{
private:
	ObjectType type;
public:
	sf::Sprite* sprite;
	b2Vec2 size;
	b2Vec2 position;

	b2BodyDef bodyDef;
	b2Body* body;
	b2CircleShape shape;
	b2FixtureDef fixtureDef;

	Crosshair(b2World & world, b2Vec2 _position, sf::Sprite* _sprite);
	Crosshair();
	~Crosshair();
	ObjectType GetType();
	void CreatePhysicsBody(b2World & world);
	void Update();
};
