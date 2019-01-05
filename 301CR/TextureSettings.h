#pragma once

#include "pch.h"

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

struct TextureSettings
{
public:
	std::string filePath;
	sf::Vector2i rectPixelSize;
	sf::Vector2i rectPosition;
	TextureSettings() {};
	TextureSettings(const std::string _filePath, const sf::Vector2i _rectPixelSize, const sf::Vector2i _rectPosition ) 
	{
		filePath = _filePath;
		rectPixelSize = _rectPixelSize;
		rectPosition = _rectPosition;
	};
};
