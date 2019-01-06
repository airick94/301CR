#pragma once
#include "pch.h"

#include "GameSettings.h"
#include "Enums.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "Animation.h"
#include "Animator.h"
#include "Projectile.h"
#include "Crosshair.h"

class Player
{
private:
	ObjectType type;
	Crosshair* crosshair;
	std::vector<Projectile*> projectiles;
public:

	sf::Sprite* sprite;
	b2Vec2 size;
	b2Vec2 position;

	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	Animator animator;

	std::vector<Animation> animations;

	sf::Clock clock;
	int currentFrameID = 0;

	Player();
	Player(b2World & world, std::vector<Animation> _animations, b2Vec2 _position, b2Vec2 _size);
	void CreatePhysicsBody(b2World& world);

	void Move(MoveState toState);

	void AddProjectile(Projectile* proj);

	void Update();

	void SetCrosshair(Crosshair * _crosshair);

	Crosshair * GetCrosshair();

	std::vector<Projectile*> GetProjectiles();
	
};