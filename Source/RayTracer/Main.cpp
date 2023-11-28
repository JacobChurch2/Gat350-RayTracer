#include "Renderer.h"
#include "Random.h"
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
	}

		//<shutdown renderer>
	renderer.Shutdown();

	return 0;
}