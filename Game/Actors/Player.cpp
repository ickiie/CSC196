#include "Player.h"
#include "MathUtils.h"

void Player::Update(float dt) {

	Actor::Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
}