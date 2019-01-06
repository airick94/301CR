
#include "pch.h"
#include <iostream>
#include "GameSettings.h"

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "ContactListener.h"
#include "Enums.h"
#include "Player.h"
#include "Ground.h"
#include "Animation.h"
#include "GraphicsSystem.h"

int main()
{
	/** Prepare the window */
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test", sf::Style::Close);
	Window.setFramerateLimit(60);
	Window.setMouseCursorVisible(false);

	sf::View view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(800, 600));
	Window.setView(view);

	/** Prepare the world */
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);

	//b2Body* ground = CreateGround(World, 400.f, 500.f, OT_Ground);

	/** Prepare textures */
	sf::Texture GroundTexture;
	sf::Texture BoxTexture;
	sf::Texture CrosshairTexture;
	GroundTexture.loadFromFile("ground.png");
	BoxTexture.loadFromFile("box.png");
	CrosshairTexture.loadFromFile("crosshair2.png");


	sf::Texture grassLeft;
	sf::Texture grassMid;
	sf::Texture grassRight;

	/*grassLeft.loadFromFile("Assets/Enemies_128x128/Spike_down.png");
	grassMid.loadFromFile("Assets/Enemies_128x128/Spike_right.png");
	grassRight.loadFromFile("Assets/Enemies_128x128/Spike_Up.png");*/

	grassLeft.loadFromFile("Assets/Level_Spring_128x128/GrassLeft.png");
	grassMid.loadFromFile("Assets/Level_Spring_128x128/GrassMid.png");
	grassRight.loadFromFile("Assets/Level_Spring_128x128/GrassRight.png");

	sf::Sprite grassLeftSprite;
	sf::Sprite grassMidSprite;
	sf::Sprite grassRightSprite;
	grassLeftSprite.setTexture(grassLeft);
	grassMidSprite.setTexture(grassMid);
	grassRightSprite.setTexture(grassRight);
	grassLeftSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	grassMidSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	grassRightSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));

	std::vector<sf::Sprite*> grassSprites = std::vector<sf::Sprite*>{
		&grassLeftSprite,
		&grassMidSprite,
		&grassRightSprite 
	};
	b2Vec2 groundSize = b2Vec2(18, 3);
	Ground ground = Ground(&World, b2Vec2(10, 7), groundSize, grassSprites, 18);
	Ground ground2 = Ground(&World, b2Vec2(30, 7), groundSize, grassSprites, 18);

	int numberOfSpritesInGround = 6;

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("spritesheet_1024x1024.png");
	spriteSheet.setSmooth(true);

	Animation idle = Animation("idle", spriteSheet, sf::Vector2i(0, 38), sf::Vector2i(128, 143), 8);
	Animation walk = Animation("walk", spriteSheet, sf::Vector2i(0, 252), sf::Vector2i(128, 143), 6);

	std::vector<Animation> animations = std::vector<Animation>{ idle, walk };

	Player player = Player(World, animations, b2Vec2(2,2), b2Vec2(3,3));

	ContactListener contactListener;
	World.SetContactListener(&contactListener);


	bool isEditMode = false;

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				Window.close();
			if (Event.type == sf::Event::KeyPressed)
			{
				if (!isEditMode)
				{
					if (Event.key.code == sf::Keyboard::A)
					{
						player.Move(MS_Left);
					}
					if (Event.key.code == sf::Keyboard::D)
					{
						player.Move(MS_Right);
					}
					if (Event.key.code == sf::Keyboard::Space)
					{
						if (contactListener.IsColliding(player.body, ground.GetBody()))
						{
							player.Move(MS_Jump);
						}
					}
				}

			}
			if (Event.type == sf::Event::KeyReleased)
			{
				if (Event.key.code == sf::Keyboard::Num1) 
				{
					isEditMode = !isEditMode;
				}

				if (isEditMode)
				{
					if (Event.key.code == sf::Keyboard::F1)
					{
						numberOfSpritesInGround++;
						std::cout << numberOfSpritesInGround << std::endl;
					}
					if (Event.key.code == sf::Keyboard::F2)
					{
						numberOfSpritesInGround--;
						std::cout << numberOfSpritesInGround << std::endl;
					}
				}
				
			}
		}

		//UPDATE
		World.Step(1 / 60.f, 8, 3);

		player.Update();
		ground.Update();

		Window.clear(sf::Color::White);



		sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);
		if (isEditMode)
		{
			view.setCenter(mousePosition.x, mousePosition.y);
		}
		else
		{
			view.setCenter(player.position.x* SETTINGS_SCALE, player.position.y * SETTINGS_SCALE);
		}
		
		Window.setView(view);



		sf::Sprite CrosshairSprite;
		sf::Sprite ProjectileSprite;


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player.CreateProjectile(World);
			b2Vec2 direction = player.crosshair.body->GetPosition() - player.body->GetPosition();
			float strength = SETTINGS_BULLETSPEED;
			player.projectile.body->SetLinearVelocity(strength * direction);
		}

		int BodyCount = 0;
		Window.draw(player.sprite);
		for (int i = 0; i < ground.GetSpriteCount(); i++)
		{
			Window.draw(ground.GetSprite(i));
		}
		for (int i = 0; i < ground2.GetSpriteCount(); i++)
		{
			Window.draw(ground2.GetSprite(i));
		}

		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if ((int)BodyIterator->GetUserData() == (int)OT_Crosshair)
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