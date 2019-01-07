#pragma once
#include "pch.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include "GameObject.h"
#include "GroundProperties.h"
#include "CollectibleProperties.h"
#include "LevelProperties.h"
#include "Ground.h"
#include "Collectible.h"

static class LevelLoader
{
public:

	static LevelProperties LoadObjectsFromFile(std::string filePath);
	static GroundProperties* ConstructGroundProperties(std::vector<std::string> strings);
	static CollectibleProperties* ConstructCollectibleProperties(std::vector<std::string> strings);
	static b2Vec2 StringToB2Vec2(std::string text);
	static void SaveToFile(std::vector<GameObject*> gameObjects, std::string filePath);
	static std::string StringifyGround(GroundProperties prop);
};
