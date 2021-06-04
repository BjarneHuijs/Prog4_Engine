#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>

#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Idiot_Engine::Renderer::Init(/*SDL_Window * window*/)
{
	m_Window = SDL_CreateWindow(
		"This engine doesn't know what it's doing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	
	m_Renderer = SDL_CreateRenderer(m_Window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void Idiot_Engine::Renderer::Render(const float nextFrameTime) //const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render(nextFrameTime);

	// ImGui demo window
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	Player1Controls();
	Player2Controls();

	
	//if (m_ShowDemo) ImGui::ShowDemoWindow(&m_ShowDemo);
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	
	SDL_RenderPresent(m_Renderer);
}

void Idiot_Engine::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
}

void Idiot_Engine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Idiot_Engine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Idiot_Engine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, SDL_Rect source, SDL_Rect destination) const
{
	destination.x += (int)x;
	destination.y += (int)y;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &source, &destination);
}

void Idiot_Engine::Renderer::Player1Controls()
{
	// Player 1
	ImGui::Begin("Player 1: Controller");
	if (ImGui::BeginTable("Controls", 2, ImGuiTableFlags_SizingFixedFit))
	{
		ImGui::TableNextColumn();
		ImGui::Text("Kill Coily:");
		ImGui::TableNextColumn();
		ImGui::Text("A");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Catch Slicky or Sam:");
		ImGui::TableNextColumn();
		ImGui::Text("B");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Change Color:");
		ImGui::TableNextColumn();
		ImGui::Text("X");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Kill Self:");
		ImGui::TableNextColumn();
		ImGui::Text("Y");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Calculate discs score:");
		ImGui::TableNextColumn();
		ImGui::Text("Right Shoulder");
		ImGui::EndTable();
	}
	ImGui::End();
}

void Idiot_Engine::Renderer::Player2Controls()
{
	// Player 2
	ImGui::Begin("Player 2: Keyboard");
	if (ImGui::BeginTable("Controls", 2, ImGuiTableFlags_SizingFixedFit))
	{
		ImGui::TableNextColumn();
		ImGui::Text("Kill Coily:");
		ImGui::TableNextColumn();
		ImGui::Text("1");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Catch Slicky or Sam:");
		ImGui::TableNextColumn();
		ImGui::Text("3");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Change Color:");
		ImGui::TableNextColumn();
		ImGui::Text("2");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Kill Self:");
		ImGui::TableNextColumn();
		ImGui::Text("E");

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Calculate discs score:");
		ImGui::TableNextColumn();
		ImGui::Text("4");
		ImGui::EndTable();
	}
	ImGui::End();
}
