#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <vector>

nc::Vector2 position{ 400, 300 };
std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 5 }, { -5, -5 } };
nc::Shape shape{ points, nc::Color{ 1, 0, 1} };
const float speed = 5;
float timer = 0;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	timer += dt * 5;
	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//position.x = static_cast<float>(x);
	//position.y = static_cast<float>(y);

	nc::Vector2 input;
	if (Core::Input::IsPressed('A')) input.x = -1;
	if (Core::Input::IsPressed('D')) input.x = 1;
	if (Core::Input::IsPressed('W')) input.y = -1;
	if (Core::Input::IsPressed('S')) input.y = 1;

	position += input * speed;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	
	float scale = 1 + (std::sin(timer) + 1) * 2;
	shape.Draw(graphics, position);


}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
