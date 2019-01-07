#include "pch.h"
#include "LevelLoader.h"
using namespace std;
LevelProperties LevelLoader::LoadObjectsFromFile(std::string filePath)
{
	vector<vector<string>> fileAsStrings;

	int start = 0;

	ifstream myfile(filePath);
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			vector<string> lineAsStrings;
			string current;
			int it = 0;

			while (it != line.size())
			{
				if (line.at(it) == '{' || line.at(it) == ';' || line.at(it) == '}')
				{
					for (int i = start; i < it; i++)
					{
						current += line.at(i);
					}
					lineAsStrings.push_back(current);
					current = "";
					start = it+1;
				}
				it++;

			}
			start = 0;

			fileAsStrings.push_back(lineAsStrings);
		}
		myfile.close();
	}

	LevelProperties properties;
	vector<GroundProperties*> groundProps;
	vector<CollectibleProperties*> collProps;
	for (int i = 0; i < fileAsStrings.size(); i++)
	{
		if (fileAsStrings[i][0] == "GROUND")
		{
			GroundProperties* prop = ConstructGroundProperties(fileAsStrings[i]);
			groundProps.push_back(prop);
		}
		else if (fileAsStrings[i][0] == "COLLECTIBLE")
		{
			CollectibleProperties* prop = ConstructCollectibleProperties(fileAsStrings[i]);
			collProps.push_back(prop);
		}
	}

	properties.groundProps = groundProps;
	properties.collProps = collProps;


	return properties;
}

GroundProperties* LevelLoader::ConstructGroundProperties(vector<string> strings)
{
	GroundProperties* properties = new GroundProperties();

	properties->leftTexturePath = strings[1];
	properties->midTexturePath = strings[2];
	properties->rightTexturePath = strings[3];

	b2Vec2 vec = StringToB2Vec2(strings[4]);
	properties->size = vec;

	b2Vec2 vec2 = StringToB2Vec2(strings[5]);
	properties->position = vec2;

	int number = stoi(strings[6]);
	properties->numberOfSpriteSegments = number;

	return properties;
}

CollectibleProperties* LevelLoader::ConstructCollectibleProperties(vector<string> strings)
{
	CollectibleProperties* properties = new CollectibleProperties();

	for (int i = 1; i < strings.size(); i++)
	{
		if (i == strings.size() - 3)
		{
			b2Vec2 vec = StringToB2Vec2(strings[i]);
			properties->size = vec;
		}
		else if (i == strings.size() - 2)
		{
			b2Vec2 vec = StringToB2Vec2(strings[i]);
			properties->position = vec;
		}
		else if (i == strings.size() - 1)
		{
			int number = stoi(strings[i]);
			properties->numberOfFrames = number;
		}
		else
		{
			properties->texturePaths.push_back(strings[i]);
		}
	}

	return properties;
}

b2Vec2 LevelLoader::StringToB2Vec2(std::string text)
{
	string x;
	string y;
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == ',')
		{
			for (int j = 0; j < i; j++)
			{
				x += text[j];
			}
			for (int k = i + 1; k < text.size(); k++)
			{
				y += text[k];
			}
		}
	}

	return b2Vec2(stof(x), stof(y));
}

void LevelLoader::SaveToFile(vector<GameObject*> gameObjects, string filePath)
{
//	isFinished = false;
	ofstream textFile(filePath);
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetType() == OT_NewGround)
		{
			Ground* ground = dynamic_cast<Ground*>(gameObjects[i]);
			GroundProperties prop = GroundProperties();
			prop.leftTexturePath = ground->texturepaths[0];
			prop.midTexturePath = ground->texturepaths[1];
			prop.rightTexturePath = ground->texturepaths[2];
			prop.size = ground->GetSize();
			prop.position = ground->GetPosition();
			prop.numberOfSpriteSegments = ground->GetNumberOfSegments();

			string line = StringifyGround(prop);
			
			textFile << line;
			

		}
		else if (gameObjects[i]->GetType() == OT_Collectible)
		{
			Collectible* collectible = dynamic_cast<Collectible*>(gameObjects[i]);


		}
	}
	textFile.flush();
	textFile.close();

}

string LevelLoader::StringifyGround(GroundProperties prop)
{
	string final;
	string text1 = "GROUND";
	string text2 = "{";
	string text3 = prop.leftTexturePath + ";";
	string text4 = prop.midTexturePath + ";";
	string text5 = prop.rightTexturePath + ";";
	string text6 = std::to_string(prop.size.x) + "," + std::to_string(prop.size.y) + ";";
	string text7 = std::to_string(prop.position.x) + "," + std::to_string(prop.position.y) + ";";
	string text8;
	if (prop.numberOfSpriteSegments == 0)
	{
		text8 = "0}\n";
	}
	else
	{
		text8 = std::to_string(prop.numberOfSpriteSegments) + "}\n";
	}

	final = text1 + text2 + text3 + text4 + text5 + text6 + text7+ text8;
	return final;
}
