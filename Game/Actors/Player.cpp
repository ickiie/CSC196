#include "Player.h"
#include "Projectile.h"
#include "Engine.h"
#include "MathUtils.h"
#include <memory>

void Player::Update(float dt) {

	Actor::Update(dt);

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	// fire
	if (Core::Input::IsPressed(VK_SPACE)) {

		std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 } };
		std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });

		nc::Transform t = transform;
		t.scale = 0.5f;
		scene->AddActor(std::make_unique<Projectile>(t, shape, 600.0f));
	}

}