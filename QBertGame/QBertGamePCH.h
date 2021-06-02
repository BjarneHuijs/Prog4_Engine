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
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2.lib")

#define Safe_Delete(p) if ((p) != NULL) { delete (p); (p) = NULL; }