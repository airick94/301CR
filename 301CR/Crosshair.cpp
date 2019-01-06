#include "pch.h"
#include "Crosshair.h"

Crosshair::Crosshair(b2World & world, b2Vec2 _position, sf::Sprite * _sprite)
{
	position = _position;
	type = ObjectType::OT_Projectile;
	CreatePhysicsBody(world);

	sprite = _sprite;

	sprite->setPosition(position.x * SETTINGS_SCALE, position.y * SETTINGS_SCALE);
	sprite->setRotation(180 / b2_pi * body->GetAngle());
	body->SetTransform(position,body->GetAngle());
}

Crosshair::Crosshair()
{
}

Crosshair::~Crosshair()
{
}

ObjectType Crosshair::GetType()
{
	return type;
}

void Crosshair::CreatePhysicsBody(b2World & world)
{
	bodyDef.position = position;
	bodyDef.type = b2_staticBody;
	body = world.CreateBody(&bodyDef);

	shape.m_radius = 1;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 1.0f;
	fixtureDef.shape = &shape;

	body->CreateFixture(&fixtureDef);

	body->SetUserData((void*)GetType());
}

void Crosshair::Update()
{
	position = body->GetPosition();
	sprite->setPosition(sf::Vector2f(position.x * SETTINGS_SCALE, position.y * SETTINGS_SCALE));
}
