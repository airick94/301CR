#include "pch.h"
#include "Ground.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

Ground::Ground(b2World * _world, b2Vec2 _position, b2Vec2 _size, std::vector<sf::Sprite*> _sprites, int _numberOfSpriteSegments)
{
	type = OT_NewGround;

	world = _world;
	position = _position;
	size = _size;
	baseSprites = _sprites;

	numberOfSpriteSegments = _numberOfSpriteSegments;
	CreatePhysicsBody();
	SetupSprites(_numberOfSpriteSegments);
}

b2Body * Ground::GetBody()
{
	return body;
}

sf::Sprite&  Ground::GetSprite(int id)
{
	return sprites[id];
}

sf::Sprite Ground::GetBaseSprite(int id)
{
	return *baseSprites[id];
}

int Ground::GetSpriteCount()
{
	return sprites.size();
}

void Ground::CreatePhysicsBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = position;
	BodyDef.type = b2_staticBody;
	body = world->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(size.x / 2, size.y / 2);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	FixtureDef.friction = 0.5f;

	FixtureDef.filter.categoryBits = 0x0002;
	FixtureDef.filter.maskBits = 0x0002;


	body->CreateFixture(&FixtureDef);
	body->SetUserData((void*)type);
}

void Ground::SetupSprites(int numberOfSprites)
{
	sprites.clear();
	sprites.resize(numberOfSprites);
	sf::Sprite sprite;
	for (int i = 0; i < numberOfSprites; i++)
	{
		if (i == 0)
		{
			sprite = GetBaseSprite(0);
		}
		else if (i == numberOfSprites -1)
		{
			sprite = GetBaseSprite(2);
		}
		else
		{
			sprite = GetBaseSprite(1);
		}

		sf::IntRect rect = sprite.getTextureRect();
		sprite.setOrigin(rect.width / 2, rect.height / 2);
		float groundSizePixelX = size.x * SETTINGS_SCALE;
		float groundSizePixelY = size.y * SETTINGS_SCALE;
		float scaleX = (groundSizePixelX / rect.width) / numberOfSprites;
		float scaleY = groundSizePixelY / rect.height;
		sprite.setScale(scaleX, scaleY);

		float bodyPositionX = body->GetPosition().x * SETTINGS_SCALE;
		float bodyPositionY = body->GetPosition().y * SETTINGS_SCALE;

		float spritePositionX = bodyPositionX + (i * size.x * SETTINGS_SCALE / numberOfSprites);
		float offSetX = size.x / 2 * SETTINGS_SCALE;

		spritePositionX -= offSetX;

		sprite.setPosition(spritePositionX, bodyPositionY);
		sprite.setRotation(180 / b2_pi * body->GetAngle());

		sprites[i] = sprite;
	}
}

void Ground::Update()
{
	b2Vec2 difference = position - body->GetPosition(); //remember previous position so we can update sprites

	body->SetTransform(position, body->GetAngle());

	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i].setPosition(sprites[i].getPosition().x + difference.x * SETTINGS_SCALE, sprites[i].getPosition().y + difference.y * SETTINGS_SCALE);
	}
}

b2Vec2 Ground::GetSize()
{
	return size;
}

int Ground::GetNumberOfSegments()
{
	return numberOfSpriteSegments;
}
