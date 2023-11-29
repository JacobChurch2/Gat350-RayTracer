#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include <iostream>
#include <SDL.h>

using namespace std;

int main(int, char**)
{
	std::cout << "hello world!\n";
	seedRandom((uint32_t)time(nullptr));

	//<create renderer>
	Renderer renderer;
	//<initialize renderer>
	renderer.Initialize();
	//<create renderer window with size of 400, 300>
	renderer.CreateWindow("The Window", 400, 300);
	Canvas canvas(400, 300, renderer);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({random01() * canvas.GetSize().x, random01() * canvas.GetSize().y}, {random01(), random01(), random01(), 1});
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	//<shutdown renderer>
	renderer.Shutdown();

	return 0;
}