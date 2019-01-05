#include "pch.h"
#include "Animator.h"

Animator::Animator()
{
}

Animator::Animator(const sf::Sprite& _sprite, std::vector<Animation>& _animations)
{
	sprite = _sprite;
	animations = _animations;

	currentAnimation = animations[0];
}

void Animator::Update()
{
	currentAnimation.Update();
}

void Animator::StartAnimation(std::string name)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i].name == name)
		{
			currentAnimation = animations[i];
			currentAnimation.Play(sprite);
		}
	}
}
