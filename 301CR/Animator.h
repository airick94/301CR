#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Animator
{
private:
	
	Animation* currentAnimation;
public:
	sf::Sprite* sprite;
	std::vector<Animation> animations;

	Animator();
	//Animator(sf::Sprite& _sprite, std::vector<Animation>& _animations);

	void Update();
	void StartAnimation(std::string name);
	Animation* GetCurrentAnimation();
	Animation* GetAnimationByName(std::string name);
};