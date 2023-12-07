#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Materials.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"
#include <memory>
#include <iostream>
#include <SDL.h>

using namespace std;

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void CornellBox(Scene& scene, const Canvas& canvas);
void FinalScene(Scene& scene, const Canvas& canvas);

int main(int, char**)
{
	const int width = 400;
	const int height = 300;
	const int samples = 500;
	const int depth = 8;

	seedRandom((uint32_t)time(nullptr));

	//<create renderer>
	Renderer renderer;
	//<initialize renderer>
	renderer.Initialize();
	//<create renderer window with size of 400, 300>
	renderer.CreateWindow("The Window", width, height);

	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 1 }, glm::vec3{ 0 });

	CornellBox(scene, canvas);

	// render scene 
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();

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

		/*canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({random01() * canvas.GetSize().x, random01() * canvas.GetSize().y}, {random01(), random01(), random01(), 1});
		canvas.Update();*/

		//renderer.PresentCanvas(canvas);

		/*canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();*/

		renderer.PresentCanvas(canvas);
	}

	//<shutdown renderer>
	renderer.Shutdown();

	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));

	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 1 }, 10));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void CornellBox(Scene& scene, const Canvas& canvas) {
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 100.0f, aspectRatio);
	scene.SetCamera(camera);

	/*auto left = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	left->Load("models/quad.obj", glm::vec3{ -2, 0, 0 }, glm::vec3{ 0, 90, 0 }, glm::vec3{4});
	scene.AddObject(std::move(left));

	auto right = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
	right->Load("models/quad.obj", glm::vec3{ 2, 0, 0 }, glm::vec3{ 0, -90, 0 }, glm::vec3{ 4 });
	scene.AddObject(std::move(right));

	auto floor = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1}));
	floor->Load("models/quad.obj", glm::vec3{ 0, -2, 0 }, glm::vec3{ -90, 0, 0 }, glm::vec3{ 4 });
	scene.AddObject(std::move(floor));

	auto ceiling = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1 }));
	ceiling->Load("models/quad.obj", glm::vec3{ 0, 2, 0 }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 4 });
	scene.AddObject(std::move(ceiling));

	auto back = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1 }));
	back->Load("models/quad.obj", glm::vec3{ 0 , 0, -2 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 4 });
	scene.AddObject(std::move(back));*/

	auto left = std::make_unique<Plane>(glm::vec3{ -2, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1,0,0 }));
	scene.AddObject(std::move(left));

	auto right = std::make_unique<Plane>(glm::vec3{ 2, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0,1,0 }));
	scene.AddObject(std::move(right));

	auto back = std::make_unique<Plane>(glm::vec3{ 0, 0, -2 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(back));

	auto floor = std::make_unique<Plane>(glm::vec3{ 0, -2, 0}, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(floor));

	auto celing = std::make_unique<Plane>(glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(celing));

	auto cube = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	cube->Load("models/cube.obj", glm::vec3{ -1, -1.5, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(cube));

	auto sphere = std::make_unique<Sphere>(glm::vec3{ 1, -1.5, 1 }, 0.5f, std::make_shared<Lambertian>(color3_t{ 1 }));
	// add sphere to the scene
	scene.AddObject(std::move(sphere));

	auto light = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 5));
	light->Load("models/cube.obj", glm::vec3{ 0, 2, 0 }, glm::vec3{ 0, 0, 0 });
	scene.AddObject(std::move(light));
}

void FinalScene(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));

	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{1, 0, 0.7f}));
	scene.AddObject(std::move(plane));
}