#pragma once
#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// SDL Includes
#define SDL_MAIN_HANDLED
#pragma comment(lib, "SDL2_mixer.lib")
#include <SDL_mixer.h>
#pragma comment(lib, "SDL2_image.lib")
#include <SDL_image.h>
#pragma comment(lib, "SDL2_ttf.lib")
#include <SDL_ttf.h>
#pragma comment(lib, "SDL2.lib")
#include <SDL.h>

#pragma warning (disable:4201)
#pragma warning (disable:4189)
#include <glm/vec2.hpp>

#define Safe_Delete(p) if ((p) != NULL) { delete (p); (p) = NULL; }