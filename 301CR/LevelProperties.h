#pragma once
#include "pch.h"
#include <iostream>
#include <vector>

#include "GroundProperties.h"
#include "CollectibleProperties.h"
struct LevelProperties
{
public:
	std::vector<GroundProperties*>		groundProps;
	std::vector<CollectibleProperties*> collProps;
};