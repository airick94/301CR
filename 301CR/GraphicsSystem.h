#pragma once

#include "pch.h"

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "Animation.h"

static class GraphicsSystem
{
public:
	GraphicsSystem();
	static void GetNewSprite(sf::Sprite& sprite, Animation settings);
};