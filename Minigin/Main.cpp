#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#define DemoWindows

#include "SDL.h"
#include "Minigin.h"

// No longer needed -> this is a static library now
//int main(int, char*[]) {
//	Idiot_Engine::Minigin engine;
//	engine.Run();
//    return 0;
//}