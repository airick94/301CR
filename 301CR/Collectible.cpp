#include "pch.h"
#include "Collectible.h"


Collectible::Collectible()
{
}


Collectible::~Collectible()
{
}

Collectible::Collectible(b2World & world, b2Vec2 _position, b2Vec2 _size, std::vector<Animation> _animations)
{
	type = ObjectType::OT_Collectible;
	position = _position;
	size = _size;

	sprite = new sf::Sprite();

	animator.animations = _animations;
	animator.sprite = sprite;
	animator.StartAnimation("spin");

	sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
	float scaleX = (_size.x / sprite->getTextureRect().width) * SETTINGS_SCALE;
	float scaleY = (_size.y / sprite->getTextureRect().height) * SETTINGS_SCALE;
	sprite->setScale(sf::Vector2f(scaleX, scaleY));
	
	CreatePhysicsBody(world);

	sprite->setPosition(sf::Vector2f(position.x * SETTINGS_SCALE, position.y * SETTINGS_SCALE));

}



void Collectible::CreatePhysicsBody(b2World & world)
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

	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;

	body->CreateFixture(&fixtureDef);

	body->SetUserData((void*)type);
}

void Collectible::Update(ContactListener listener, Player player)
{
	if (IsEnabled())
	{
		animator.Update();
		sprite->setPosition(sf::Vector2f(position.x * SETTINGS_SCALE, position.y * SETTINGS_SCALE));

		if (listener.IsColliding(player.GetBody(), body))
		{
			player.IncreasePoints(1);
			Die();
		}
	}
	
}
void Collectible::Die()
{
	body->GetWorld()->DestroyBody(body);
	enabled = false;
}
