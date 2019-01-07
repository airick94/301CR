#pragma once
#include "pch.h"
#include <iostream>
#include "Box2D/Box2D.h"

struct GroundProperties
{
public:
	std::string leftTexturePath;
	std::string midTexturePath;
	std::string rightTexturePath;
	b2Vec2 size;
	b2Vec2 position;
	int numberOfSpriteSegments;
};

