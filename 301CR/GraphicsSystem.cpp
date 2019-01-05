#include "pch.h"
#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem()
{
}

void GraphicsSystem::GetNewSprite(sf::Sprite& sprite, TextureSettings settings)
{
	sf::Texture texture;
	texture.loadFromFile(settings.filePath);

	sf::IntRect rect = sf::IntRect(settings.rectPosition, settings.rectPixelSize);

	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}
