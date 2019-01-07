#pragma once

#include "pch.h"
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "GameSettings.h"
#include "GameObject.h"

class Crosshair : public GameObject
{
public:

	Crosshair(b2World & world, b2Vec2 _position, sf::Texture& _texture);
	Crosshair();
	~Crosshair();
	void CreatePhysicsBody(b2World & world);
	void Update();
};
