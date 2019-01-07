#include "pch.h"
#include "Player.h"

Player::~Player()
{
}

Player::Player()
{
}

Player::Player(b2World & world, std::vector<Animation> _animations, b2Vec2 _position, b2Vec2 _size)
{
	type = ObjectType::OT_Player;

	sprite = new sf::Sprite();

	animator.animations = _animations;
	animator.sprite = sprite;
	animator.StartAnimation("idle");

	
	sprite->setOrigin(sprite->getTextureRect().width / 2, sprite->getTextureRect().height / 2);
	float scaleX = (_size.x / sprite->getTextureRect().width) * SETTINGS_SCALE;
	float scaleY = (_size.y / sprite->getTextureRect().height) * SETTINGS_SCALE;
	sprite->setScale(sf::Vector2f(scaleX, scaleY));

	size = _size;
	position = _position;

	CreatePhysicsBody(world);

	body->SetUserData((void*)type);

}

void Player::CreatePhysicsBody(b2World & world)
{
	b2BodyDef bodyDef;

	bodyDef.position = b2Vec2(position.x, position.y);
	bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape shape;
	shape.SetAsBox((size.x / 2), (size.y / 2));

	b2FixtureDef fixtureDef;
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

		
		if (sprite->getScale().x > 0)
		{
			sprite->scale(-1, 1);
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

		if (sprite->getScale().x < 0)
		{
			sprite->scale(-1, 1);
		}
		break;
	}

	body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldCenter(), true);
}

void Player::AddProjectile(Projectile * proj)
{
	projectiles.push_back(proj);
}

void Player::Update()
{
	position = body->GetPosition();
	sprite->setPosition(SETTINGS_SCALE * position.x, SETTINGS_SCALE * position.y);
	sprite->setRotation(body->GetAngle() * 180 / b2_pi);

	if (animator.GetCurrentAnimation() != animator.GetAnimationByName("walk"))
	{
		if (abs(body->GetLinearVelocity().x) > 0.05)
		{
			animator.StartAnimation("walk");
		}
	}
	else
	{
		if (abs(body->GetLinearVelocity().x) < 0.05)
		{
			animator.StartAnimation("idle");
		}
	}

	animator.Update();
}

void Player::SetCrosshair(Crosshair * _crosshair)
{
	crosshair = _crosshair;
}

Crosshair* Player::GetCrosshair()
{
	return crosshair;
}

std::vector<Projectile*> Player::GetProjectiles()
{
	return projectiles;
}

void Player::IncreasePoints(int amount)
{
	points += amount;
}
