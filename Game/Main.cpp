#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

#include <iostream>
#include <vector>
#include <string>


std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 } };
//nc::Transform transform{ {400, 300}, 0, 3 };

float timer = 0;
nc::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

nc::Engine engine;
nc::Scene scene;


bool Update(float dt)
{

	deltaTime = dt;
	gameTime += deltaTime;

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
		engine.Get<nc::AudioSystem>()->PlayAudio("explosion");
	}

	//engine.Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, nc::Color::white, 50);

	scene.GetActor<Player>()->shape->color = nc::Color{ nc::Random(), nc::Random(), nc::Random() };
	scene.GetActor<Enemy>()->shape->color = nc::Color{ nc::Random(), nc::Random(), nc::Random() };

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
	graphics.DrawString(10, 50, std::to_string(scene.GetActors<Projectile>().size()).c_str());

}

void Init() {

	std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
	shape->Load("shape.txt");


	std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 0, 1, 0 });
	std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });

	//Audio
	engine.Get<nc::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	scene.AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 3.0f), shape, 300.0f));
	for (size_t i = 0; i < 10; i += 1) {

		scene.AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, shape2, 300.0f));
	}
}

class A
{
public:
	virtual void Display() { std::cout << "A\n"; }
};

class B : public A
{
public:
	void Display() override { std::cout << "B\n"; }
	void BFunc() { std::cout << "B Func\n"; }
};

class C : public A
{
public:
	void Display() override { std::cout << "C\n"; }
	void CFunc() { std::cout << "C Func\n"; }
};


int main()
{

	A* a = new A;
	A* b = new B;
	C* c = new C;

	a->Display();
	b->Display();
	dynamic_cast<C*>(b)->CFunc();
	c->Display();

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
