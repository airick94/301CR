#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animator.h"
#include "ContactListener.h"
#include "Player.h"

class Collectible : public GameObject
{
public:
	Animator animator;
	std::vector<Animation> animations;
	sf::Clock clock;
	int currentFrameID = 0;

	Collectible();
	~Collectible();
	Collectible(b2World & world, b2Vec2 _position, b2Vec2 _size, std::vector<Animation> _animations);
	void CreatePhysicsBody(b2World & world);
	void Update(ContactListener listener, Player player);
	void Die();
};

