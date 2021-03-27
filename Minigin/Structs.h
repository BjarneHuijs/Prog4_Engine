#pragma once

enum class EventTypes
{
	PlayerDeath,
	LivesChanged,
	ScoreChanged,
	All
};

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a{ 255 };
};

struct Event
{
	std::string message;
	EventTypes type;
};

