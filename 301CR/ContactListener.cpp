#include "pch.h"
#include "ContactListener.h"

#include <iostream>
#include <iterator>

ContactListener::ContactListener() {};
ContactListener::~ContactListener() {};

CollidePair::CollidePair() {};
CollidePair::CollidePair(b2Body * _body1, b2Body * _body2)
{
	body1 = _body1;
	body2 = _body2;
}

bool CollidePair::Equals(CollidePair other)
{
	if ((int)body1->GetUserData() == (int)other.body1->GetUserData() && (int)body2->GetUserData() == (int)other.body2->GetUserData())
	{
		return true;
	}
	if ((int)body2->GetUserData() == (int)other.body1->GetUserData() && (int)body1->GetUserData() == (int)other.body2->GetUserData())
	{
		return true;
	}

	return false;
}

//Gets called when 2 physics objects come into contact with each other
//adds a collidePair to internal collision list
void ContactListener::BeginContact(b2Contact* contact)
{
	//Adding them to internal list so we can query it later
	CollidePair pair = CollidePair((b2Body*)contact->GetFixtureA()->GetBody(), (b2Body*)contact->GetFixtureB()->GetBody());

	collisionList.push_back(pair);
}

//Gets called when 2 objects stop being in contact with each other
//removes the collidePair from internal collision list
void ContactListener::EndContact(b2Contact* contact)
{
	CollidePair pair = CollidePair(contact->GetFixtureA()->GetBody(), contact->GetFixtureB()->GetBody());

	int positionToRemove = 0;
	std::vector<CollidePair>::iterator it = collisionList.begin();

	for (int i = 0; i < collisionList.size(); i++)
	{
		if (collisionList[i].Equals(pair))
		{
			pair = collisionList[i];
			break;
		}
	}

	std::advance(it, positionToRemove);
	collisionList.erase(it);

}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	
}

//Returns true when body1 is colliding with body2
bool ContactListener::IsColliding(b2Body * body1, b2Body * body2)
{
	CollidePair pair = CollidePair(body1, body2);

	for (int i = 0; i < collisionList.size(); i++)
	{
		if (collisionList[i].Equals(pair))
		{
			return true;
		}
	}

	return false;
}


