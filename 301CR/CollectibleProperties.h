#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

struct CollectibleProperties
{
public:
	std::vector<std::string> texturePaths;
	b2Vec2 size;
	b2Vec2 position;
	int numberOfFrames;
};