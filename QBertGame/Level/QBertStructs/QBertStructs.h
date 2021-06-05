#pragma once
#include "Transform.h"
#include "glm/vec2.hpp"

enum class TileStates
{
	Base,
	Intermediate,
	Target,
};


struct TileData
{
	int TileID;
	Idiot_Engine::Transform Position;
	
	int TopLeft;
	int TopRight;
	int BotLeft;
	int BotRight;

	int SideLeft;
	int SideRight;

	float size = 50.f;
	TileStates CurrentState;
};