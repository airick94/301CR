#include "pch.h"
#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(std::string _name, const sf::Texture & _texture, const sf::Vector2i _rectPosition, const sf::Vector2i _rectPixelSize, int _numberOfFrames)
{
	isSpriteSheet = true;
	name			= _name;
	texture			= _texture;
	rectPixelSize	= _rectPixelSize;
	rectPosition	= _rectPosition;
	numberOfFrames	= _numberOfFrames;

	currentFrame = 0;
}
Animation::Animation(std::string _name, std::vector<sf::Texture> & _textures, const sf::Vector2i _rectPosition, const sf::Vector2i _rectPixelSize, int _numberOfFrames)
{
	isSpriteSheet = false;
	name = _name;
	textures = _textures;
	rectPixelSize = _rectPixelSize;
	rectPosition = _rectPosition;
	numberOfFrames = _numberOfFrames;

	currentFrame = 0;
}

sf::IntRect Animation::GetRectForFrame(int frame)
{
	return sf::IntRect(sf::Vector2i(rectPosition.x * frame,rectPosition.y), rectPixelSize);
}

int Animation::GetCurrentFrame()
{
	return currentFrame;
}

void Animation::SetCurrentFrame(int frame)
{
	currentFrame = frame;
}

void Animation::Play()
{
	isPlaying = true;
}

void Animation::Update()
{
	if (isPlaying)
	{
		if (clock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (isSpriteSheet)
			{
				sf::IntRect rect = sprite->getTextureRect();

				rect.left = currentFrame * rect.width;
				sprite->setTextureRect(rect);
				clock.restart();
			}
			else
			{
				sprite->setTexture(textures[currentFrame]);
			}
			

			if (currentFrame >= numberOfFrames - 1)
			{
				currentFrame = 0;
				if (!shouldLoop)
				{
					isPlaying = false;
				}
			}
			else
			{
				currentFrame++;
			}
		}
		
	}
}


