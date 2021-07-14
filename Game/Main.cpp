#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

#include <iostream>
#include <vector>
#include <string>


std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 } };
nc::Shape shape{ points, nc::Color{ 1, 0, 1} };
nc::Shape shape2{ points, nc::Color{ 1, 1, 1} };
//nc::Transform transform{ {400, 300}, 0, 3 };

float timer = 0;
nc::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

nc::Engine engine;
nc::Scene scene;


bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	timer += dt * 5;

	int x, y;
	Core::Input::GetMousePos(x, y);
	
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {

		std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::yellow };
		engine.Get<nc::ParticleSystem>()->Create(psPosition, 150, 2, colors[nc::RandomRangeInt(0, colors.size())], 150);

		//Audio
		//engine.Get<nc::AudioSystem>()->PlayAudio("explosion");
	}

	//engine.Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, nc::Color::white, 50);
	scene.Update(dt);
	engine.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	

	
	scene.Draw(graphics);
	engine.Get<nc::ParticleSystem>()->Draw(graphics);

	nc::Color color = nc::Lerp(nc::Color::green, nc::Color::orange, psPosition.x / 800);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());
	graphics.DrawString(10, 40, std::to_string(psPosition.Length()).c_str());

}

void Init() {

	//engine.get audio
	scene.AddActor(new Player{ nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, &shape, 300 });
	for (size_t i = 0; i < 100; i += 0) {

		scene.AddActor(new Enemy{ nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2 }, &shape2, 300 });
	}
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	engine.Startup();
	Init();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}
