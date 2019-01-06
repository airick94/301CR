#pragma once

#include "pch.h"
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "GameSettings.h"

class Projectile
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

	Projectile(b2World & world, b2Vec2 _position, sf::Texture& _texture);
	Projectile();
	~Projectile();
	ObjectType GetType();
	void CreatePhysicsBody(b2World & world);
	void Update();
};
