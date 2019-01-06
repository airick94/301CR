#pragma once
#include "pch.h"
#include <iostream>
#include <vector>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "GameSettings.h"

class Ground
{
private:
	ObjectType type;
	b2Vec2 position;
	b2Vec2 size;
	std::vector<sf::Sprite*> baseSprites;
	std::vector<sf::Sprite> sprites;
	b2World* world;
	int numberOfSpriteSegments;


	b2Body* body;
public:

	Ground();
	~Ground();
	Ground(b2World* _world, b2Vec2 _position, b2Vec2 _size, std::vector<sf::Sprite*>_sprites, int _numberOfSpriteSegments);
	
	b2Body* GetBody();
	sf::Sprite& GetSprite(int id);
	sf::Sprite GetBaseSprite(int id);
	int GetSpriteCount();
	void CreatePhysicsBody();
	void SetupSprites();
	void Update();
};
