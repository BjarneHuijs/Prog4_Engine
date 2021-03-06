#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma comment(lib, "SDL2_mixer.lib")
#include <SDL_mixer.h>

#define Safe_Delete(p) if ((p) != NULL) { delete (p); (p) = NULL; }