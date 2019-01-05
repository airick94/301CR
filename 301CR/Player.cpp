#include "pch.h"
#include "Player.h"
#include "GameSettings.h"
#include "TextureSettings.h"

Player::Player(b2World & world, const sf::Texture& _texture, b2Vec2 _size, b2Vec2 _position)
{
	type = ObjectType::OT_Player;

	sprite.setTexture(_texture);
	sf::IntRect rect = sf::IntRect(sf::Vector2i(0, 43), sf::Vector2i(128, 143));
	sprite.setTextureRect(rect);

	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	
	float scaleX = (_size.x / sprite.getTextureRect().width) * SETTINGS_SCALE;
	float scaleY = (_size.y / sprite.getTextureRect().height) * SETTINGS_SCALE;
	sprite.setScale(sf::Vector2f(scaleX, scaleY));

	size = _size;
	position = _position;

	CreatePhysicsBody(world);

	body->SetUserData((void*)type);

	CreateCrosshair(world);
}

void Player::CreatePhysicsBody(b2World & world)
{
	bodyDef.position = b2Vec2(position.x, position.y);
	bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	shape.SetAsBox((size.x / 2), (size.y / 2));
	fixtureDef.density = 1.f;
	fixtureDef.friction = 1.0f;
	fixtureDef.shape = &shape;

	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
		
	body->CreateFixture(&fixtureDef);
}

void Player::Move(MoveState toState)
{
	b2Vec2 currentvelocity = body->GetLinearVelocity();

	float velocityX = 0;
	float velocityY = 0;

	float velChangeX = 0;
	float velChangeY = 0;
	float impulseX = 0;
	float impulseY = 0;

	switch (toState)
	{
	case MS_Left:
		velocityX = -SETTINGS_MAX_HORIZONTAL_SPEED;
		velChangeX = velocityX - currentvelocity.x;
		impulseX = body->GetMass() * velChangeX;

		if (sprite.getScale().x > 0)
		{
			sprite.setScale(-1, 1);
		}
		

		break;
	case MS_Jump:
		velocityY = -SETTINGS_JUMPSTRENGTH;
		velChangeY = velocityY - currentvelocity.y;
		impulseY = body->GetMass() * velChangeY;
		break;
	case MS_Right:
		velocityX = SETTINGS_MAX_HORIZONTAL_SPEED;
		velChangeX = velocityX - currentvelocity.x;
		impulseX = body->GetMass() * velChangeX;

		if (sprite.getScale().x < 0)
		{
			sprite.setScale(1, 1);
		}
		break;
	}

	body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldCenter(), true);
}

void Player::CreateCrosshair(b2World & world)
{
	crosshair = Crosshair();

	crosshair.bodyDef.position = b2Vec2(position.x / SETTINGS_SCALE, position.y / SETTINGS_SCALE);
	crosshair.bodyDef.type = b2_staticBody;
	crosshair.body = world.CreateBody(&crosshair.bodyDef);

	crosshair.shape.m_radius = 1;
	crosshair.fixtureDef.density = 1.f;
	crosshair.fixtureDef.friction = 1.0f;
	crosshair.fixtureDef.shape = &shape;

	crosshair.body->CreateFixture(&crosshair.fixtureDef);

	crosshair.body->SetUserData((void*)crosshair.GetType());
}

void Player::CreateProjectile(b2World & world)
{
	projectile = Projectile();

	projectile.bodyDef.position = body->GetPosition();
	projectile.bodyDef.type = b2_kinematicBody;
	projectile.body = world.CreateBody(&projectile.bodyDef);

	projectile.shape.m_radius = 1;
	projectile.fixtureDef.density = 1.f;
	projectile.fixtureDef.friction = 1.0f;
	projectile.fixtureDef.shape = &shape;

	projectile.body->CreateFixture(&projectile.fixtureDef);

	projectile.body->SetUserData((void*)projectile.GetType());
}

void Player::Update()
{
	if (clock.getElapsedTime().asSeconds() > 0.1f)
	{
		if (currentFrameID > 4)
		{
			currentFrameID = 0;
		}
		else
		{
			currentFrameID++;
		}

		sf::IntRect rect = sprite.getTextureRect();

		rect.left = currentFrameID * rect.width;
		sprite.setTextureRect(rect);
		clock.restart();
	}
}

Player::Crosshair::Crosshair()
{
	type = ObjectType::OT_Crosshair;
}

ObjectType Player::Crosshair::GetType()
{
	return type;
}

Player::Projectile::Projectile()
{
	type = ObjectType::OT_Projectile;
}

ObjectType Player::Projectile::GetType()
{
	return type;
}
