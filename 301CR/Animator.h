#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Animator
{
private:
	sf::Sprite sprite;
	std::vector<Animation> animations;
	Animation currentAnimation;
public:
	Animator();
	Animator(const sf::Sprite& _sprite, std::vector<Animation>& _animations);
	void Update();
	void StartAnimation(std::string name);
};