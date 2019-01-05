#pragma once
#include "pch.h"

#include "GameSettings.h"
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "Animation.h"
#include "Animator.h"

class Player
{
private:
	ObjectType type;
public:

	class Crosshair
	{
	private:
		ObjectType type;
	public:
		sf::Texture texture;
		b2Vec2 size;
		b2Vec2 position;

		b2BodyDef bodyDef;
		b2Body* body;
		b2CircleShape shape;
		b2FixtureDef fixtureDef;

		Crosshair();
		ObjectType GetType();
	};

	class Projectile
	{
	private:
		ObjectType type;
	public:
		sf::Texture texture;
		b2Vec2 size;
		b2Vec2 position;

		b2BodyDef bodyDef;
		b2Body* body;
		b2CircleShape shape;
		b2FixtureDef fixtureDef;

		Projectile();
		ObjectType GetType();
	};

	sf::Sprite sprite;
	b2Vec2 size;
	b2Vec2 position;

	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	Crosshair crosshair;
	Projectile projectile;

	Animator animator;

	std::vector<Animation> animations;

	sf::Clock clock;
	int currentFrameID = 0;

	Player();
	Player(b2World & world, std::vector<Animation> _animations, b2Vec2 _position, b2Vec2 _size);
	void CreatePhysicsBody(b2World& world);

	void Move(MoveState toState);

	void CreateCrosshair(b2World & world);

	void CreateProjectile(b2World & world);

	void Update();

};