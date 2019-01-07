#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(b2World & world, b2Vec2 _position, sf::Texture& _texture )
{
	type = ObjectType::OT_Projectile;
	position = _position;
	
	CreatePhysicsBody(world);

	sprite = new sf::Sprite();
	sprite->setOrigin(16, 16);
	sprite->setScale(sf::Vector2f(0.5f, 0.5f));
	sprite->setTexture(_texture);
	sprite->setPosition(sf::Vector2f(position.x * SETTINGS_SCALE, position.y * SETTINGS_SCALE));
}

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::CreatePhysicsBody(b2World & world)
{
	b2BodyDef bodyDef;
	bodyDef.position = position;
	bodyDef.type = b2_kinematicBody;
	body = world.CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = 1;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 1.0f;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);

	body->SetUserData((void*)GetType());
}

void Projectile::Update()
{
	position = body->GetPosition();
	sprite->setPosition(sf::Vector2f(position.x * SETTINGS_SCALE, position.y * SETTINGS_SCALE));
}