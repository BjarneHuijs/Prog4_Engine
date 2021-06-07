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

	TileStates CurrentState = TileStates::Base;
	int LevelNr = 1;
	int NrOfColors = 2;
	float size = 50.f;
	bool cleared = false;
	bool npcOnTile = false;
	
	// sprite has 3 frames per level -> some empty for spacing when less than 3 colors
	int FramesPerLevel = 3;
	
	void SlickSamStep()
	{
		switch (CurrentState)
		{
			case TileStates::Base: break;
			case TileStates::Intermediate:
				if(NrOfColors > 2)
					CurrentState = TileStates::Base;
				break;
			case TileStates::Target: 
				CurrentState = TileStates::Intermediate;
				break;
			default: break;
		}
		cleared = false;
	};
	
	void QBertStep()
	{
		switch (CurrentState)
		{
		case TileStates::Base:
			CurrentState = TileStates::Intermediate;
			if (NrOfColors <= 2)
				cleared = true;
			break;
		case TileStates::Intermediate:
			if (NrOfColors > 2)
				CurrentState = TileStates::Target;
			cleared = true;
			break;
		case TileStates::Target:
			break;
		default: break;
		}
	}
};

struct DiscData
{
	int DiscID;
	Idiot_Engine::Transform Position;

	int ConnectedTile;
	int TargetTile;

	TileStates CurrentState = TileStates::Base;
	int LevelNr = 1;
	int NrOfColors = 2;
	float size = 16.f;
	bool Used = false;


	// sprite has 3 frames per level -> some empty for spacing when less than 3 colors
	int FramesPerLevel = 2;

	void QBertStep()
	{
		if (!Used) 
		{
			if (CurrentState == TileStates::Base)
			{
				CurrentState = TileStates::Intermediate;
				Used = true;
			}
		}
	}
};