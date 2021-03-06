#pragma once

#include "pch.h"

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

class Animation
{
private:
	int currentFrame;
	bool isPlaying = false;
	bool shouldLoop = true;
	bool isSpriteSheet;
	float speed;
	sf::Clock clock;

public:
	std::string name;
	sf::Texture texture;
	std::vector<sf::Texture> textures;
	sf::Vector2i rectPixelSize;
	sf::Vector2i rectPosition;
	int numberOfFrames;


	sf::Sprite* sprite;
	
	Animation();
	Animation(std::string _name, const sf::Texture & _texture, const sf::Vector2i _rectPosition, const sf::Vector2i _rectPixelSize, int _numberOfFrames);
	Animation(std::string _name, std::vector<sf::Texture> & _textures, const sf::Vector2i _rectPosition, const sf::Vector2i _rectPixelSize, int _numberOfFrames);
	sf::IntRect GetRectForFrame(int frame);

	int GetCurrentFrame();

	void SetCurrentFrame(int frame);

	void Play();

	void Update();
	
};
