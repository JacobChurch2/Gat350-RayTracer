#include "Renderer.h"
#include "Canvas.h"
#include <iostream>

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	//<if SDL window is not null, destroy SDL window>
	if (m_window) {
		SDL_DestroyWindow(m_window);
	}
	//<if SDL renderer is not null, destroy SDL renderer>
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
	}

	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
		//<create SDL window(https://wiki.libsdl.org/SDL2/SDL_CreateWindow Links to an external site.) >
		if (!m_window)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//<create SDL renderer(https://wiki.libsdl.org/SDL2/SDL_CreateRenderer Links to an external site.) use flags SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC>
		if (!m_renderer)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}

	return true;
}

void Renderer::PresentCanvas(const Canvas& canvas)
{
	// copy canvas texture to renderer
	SDL_RenderCopy(m_renderer, canvas.m_texture, nullptr, nullptr);
	// present renderer to screen
	SDL_RenderPresent(m_renderer);
}