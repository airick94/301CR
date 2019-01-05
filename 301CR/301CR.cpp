
#include "pch.h"
#include <iostream>
#include "GameSettings.h"

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "ContactListener.h"
#include "Enums.h"
#include "Player.h"

#include "Animation.h"
#include "GraphicsSystem.h"

/** Create the base for the boxes to land */
b2Body* CreateGround(b2World& World, float X, float Y);

void GetUserInput(Player player, b2Body* ground, ContactListener contactListener)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.Move(MS_Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.Move(MS_Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (contactListener.IsColliding(player.body, ground))
		{
			player.Move(MS_Jump);
		}
	}
 }

int main()
{
	/** Prepare the window */
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test", sf::Style::Close);
	Window.setFramerateLimit(60);
	Window.setMouseCursorVisible(false);

	/** Prepare the world */
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);

	b2Body* ground = CreateGround(World, 400.f, 500.f);

	/** Prepare textures */
	sf::Texture GroundTexture;
	sf::Texture BoxTexture;
	sf::Texture CrosshairTexture;
	GroundTexture.loadFromFile("ground.png");
	BoxTexture.loadFromFile("box.png");
	CrosshairTexture.loadFromFile("crosshair2.png");

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("spritesheet_1024x1024.png");
	spriteSheet.setSmooth(true);

	Animation idle = Animation("idle", spriteSheet, sf::Vector2i(128, 43), sf::Vector2i(128, 143), 8);
	Animation walk = Animation("walk", spriteSheet, sf::Vector2i(0, 250), sf::Vector2i(128, 143), 6);

	std::vector<Animation> animations = std::vector<Animation>{ idle, walk };

	Player player = Player(World, animations, b2Vec2(2,2), b2Vec2(3,3));

	ContactListener contactListener;
	World.SetContactListener(&contactListener);


	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				Window.close();
		}

		//UPDATE
		World.Step(1 / 60.f, 8, 3);

		GetUserInput(player, ground, contactListener);
		player.Update();

		Window.clear(sf::Color::White);

		sf::Sprite CrosshairSprite;
		sf::Sprite ProjectileSprite;

		sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player.CreateProjectile(World);
			b2Vec2 direction = player.crosshair.body->GetPosition() - player.body->GetPosition();
			float strength = SETTINGS_BULLETSPEED;
			player.projectile.body->SetLinearVelocity(strength * direction);
		}

		int BodyCount = 0;
		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if ((int)BodyIterator->GetUserData() == (int)OT_Player)
			{
				player.sprite.setPosition(SETTINGS_SCALE * BodyIterator->GetPosition().x, SETTINGS_SCALE * BodyIterator->GetPosition().y);
				player.sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);

				Window.draw(player.sprite);
				++BodyCount;
			}
			else if((int)BodyIterator->GetUserData() == (int)OT_Ground)
			{
				sf::Sprite GroundSprite;
				GroundSprite.setTexture(GroundTexture);

				GroundSprite.setOrigin(400.f, 8.f);
				GroundSprite.setPosition(BodyIterator->GetPosition().x * SETTINGS_SCALE, BodyIterator->GetPosition().y * SETTINGS_SCALE);
				GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());

				Window.draw(GroundSprite);
			}
			else if ((int)BodyIterator->GetUserData() == (int)OT_Crosshair)
			{
				CrosshairSprite.setOrigin(16, 16);
				CrosshairSprite.setScale(sf::Vector2f(0.5f, 0.5f));
				CrosshairSprite.setTexture(CrosshairTexture);

				CrosshairSprite.setPosition(mousePosition.x, mousePosition.y);
				BodyIterator->SetTransform(b2Vec2(CrosshairSprite.getPosition().x / SETTINGS_SCALE, CrosshairSprite.getPosition().y / SETTINGS_SCALE), BodyIterator->GetAngle());
				CrosshairSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());

				Window.draw(CrosshairSprite);
			}

			else if ((int)BodyIterator->GetUserData() == (int)OT_Projectile)
			{
				ProjectileSprite.setOrigin(16, 16);
				ProjectileSprite.setScale(sf::Vector2f(0.5f, 0.5f));
				ProjectileSprite.setTexture(CrosshairTexture);

				ProjectileSprite.setPosition(BodyIterator->GetPosition().x * SETTINGS_SCALE, BodyIterator->GetPosition().y * SETTINGS_SCALE);
				//BodyIterator->SetTransform(b2Vec2(ProjectileSprite.getPosition().x / SETTINGS_SCALE, ProjectileSprite.getPosition().y / SETTINGS_SCALE), BodyIterator->GetAngle());
				ProjectileSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());

				Window.draw(ProjectileSprite);
			}
		}


		Window.display();
	}

	return 0;
}

b2Body* CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SETTINGS_SCALE, Y / SETTINGS_SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SETTINGS_SCALE, (16.f / 2) / SETTINGS_SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	FixtureDef.friction = 0.5f;

	FixtureDef.filter.categoryBits = 0x0002;
	FixtureDef.filter.maskBits = 0x0002;


	Body->CreateFixture(&FixtureDef);
	Body->SetUserData((void*)OT_Ground);

	return Body;
}