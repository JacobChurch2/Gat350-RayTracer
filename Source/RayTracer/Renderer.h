#pragma once
#include <SDL.h>
#include <string>

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);
	void PresentCanvas(const class Canvas& canvas);

	friend class Canvas;

private:
	//<pointer to SDL_Window, set default value to nullptr>
	SDL_Window* m_window = nullptr;
	//<pointer to SDL_Renderer, set default value to nullptr>
	SDL_Renderer* m_renderer = nullptr;
};