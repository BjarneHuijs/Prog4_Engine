#pragma once

enum class EventTypes 
{
	PlayerDeath,
	LivesChanged,
	ScoreChanged,
	All,
	PlaySound,
	PlayMusic,
	MoveTopLeft,
	MoveTopRight,
	MoveBotLeft,
	MoveBotRight,
	TileChanged,
	DiscChanged,
};

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a{ 255 };
};

struct ObserverEvent
{
	std::string message;
	EventTypes type;
};

using SoundID = int;
using MusicID = int;
struct QueuedSound
{
	SoundID id;
	int volume;
};

struct QueuedMusic
{
	MusicID id;
	int volume;
};

//struct Channel
//{
//	bool inUse;
//	float expectedUsageTime;
//	float timeInUse;
//	int usingSoundID;
//};
