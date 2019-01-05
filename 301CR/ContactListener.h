#pragma once
#include "Box2D/Box2D.h"
#include <vector>
#include <iostream>

struct CollidePair
{
public:
	b2Body* body1;
	b2Body* body2;

	CollidePair();
	CollidePair(b2Body* _body1, b2Body* _body2);

	bool Equals(CollidePair other);
};

class ContactListener : public b2ContactListener 
{
private:
	std::vector<CollidePair> collisionList;

public:
	ContactListener();
	~ContactListener();

	virtual void BeginContact(b2Contact* contact);

	virtual void EndContact(b2Contact* contact);

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	bool IsColliding(b2Body* body1, b2Body* body2);
};