#include "Game.h"

Game game;


bool Update(float dt)
{

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//
	//psPosition.x = static_cast<float>(x);
	//psPosition.y = static_cast<float>(y);

	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {

	//	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::yellow };
	//	engine.Get<nc::ParticleSystem>()->Create(psPosition, 150, 2, colors[nc::RandomRangeInt(0, colors.size())], 150);

	//	//Audio
	//	engine.Get<nc::AudioSystem>()->PlayAudio("explosion");
	//}

	//engine.Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, nc::Color::white, 50);

	//HERE

	/*scene.GetActor<Player>()->shape->color = nc::Color{ nc::Random(), nc::Random(), nc::Random() };
	scene.GetActor<Enemy>()->shape->color = nc::Color{ nc::Random(), nc::Random(), nc::Random() };*/

	return quit;
}

void Draw(Core::Graphics& graphics)
{	
	game.Draw(graphics);
}

//HERE

//class A
//{
//public:
//	virtual void Display() { std::cout << "A\n"; }
//};
//
//class B : public A
//{
//public:
//	void Display() override { std::cout << "B\n"; }
//	void BFunc() { std::cout << "B Func\n"; }
//};
//
//class C : public A
//{
//public:
//	void Display() override { std::cout << "C\n"; }
//	void CFunc() { std::cout << "C Func\n"; }
//};

int inc(int i) { return ++i; }
int dec(int i) { return --i; }

int main()
{

	/*int (*operation)(int);
	operation = &dec;

	std::cout << operation(5) << std::endl;
	system("pause");*/


	//HERE

	/*A* a = new A;
	A* b = new B;
	C* c = new C;*/

	//HERE

	/*a->Display();
	b->Display();
	dynamic_cast<C*>(b)->CFunc();
	c->Display();*/

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}
