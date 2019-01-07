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
#include "GameObject.h"

class Player : public GameObject
{
private:
	Crosshair* crosshair;
	std::vector<Projectile*> projectiles;
	int points = 0;
public:

	Animator animator;

	std::vector<Animation> animations;

	sf::Clock clock;
	int currentFrameID = 0;
	~Player();
	Player();
	Player(b2World & world, std::vector<Animation> _animations, b2Vec2 _position, b2Vec2 _size);
	void CreatePhysicsBody(b2World& world);

	void Move(MoveState toState);

	void AddProjectile(Projectile* proj);

	void Update();

	void SetCrosshair(Crosshair * _crosshair);

	Crosshair * GetCrosshair();

	std::vector<Projectile*> GetProjectiles();
	
	void IncreasePoints(int amount);
	
};