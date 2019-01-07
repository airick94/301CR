#pragma once
#include "pch.h"
#include "GameSettings.h"
#include "SFML/Graphics.hpp"
#include "Enums.h"

class UISystem
{
private:
	sf::Text title;
	sf::Text subTitle;
	sf::Text description;
public:
	UISystem();
	~UISystem();
	void DisplayHints();
};

