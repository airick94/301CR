#include "pch.h"
#include "Animator.h"

Animator::Animator()
{
}

void Animator::Update()
{
	if (currentAnimation != NULL)
	{
		currentAnimation->Update();
	}
	
}

void Animator::StartAnimation(std::string name)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i].name == name)
		{
			currentAnimation = &animations[i];

			currentAnimation->sprite = sprite;
			currentAnimation->sprite->setTexture(currentAnimation->texture);
			sf::IntRect rect = sf::IntRect(currentAnimation->rectPosition, currentAnimation->rectPixelSize);
			currentAnimation->sprite->setTextureRect(rect);

			currentAnimation->Play();
		}
		else 
		{
			animations[i].sprite = NULL;
		}
	}
}

Animation* Animator::GetCurrentAnimation()
{
	return currentAnimation;
}

Animation * Animator::GetAnimationByName(std::string name)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations[i].name == name)
		{
			return &animations[i];
		}
	}
}
