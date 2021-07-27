#include "Player.h"
#include "Projectile.h"
#include "Engine.h"
#include "Enemy.h"
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
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {

		fireTimer = fireRate;
		
		nc::Transform t = transform;
		t.scale = 0.5f;

		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("shape.txt"), 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));

		scene->engine->Get<nc::AudioSystem>()->PlayAudio("Plaser");
	}

	scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, nc::Color::white, 50);

	transform.Update();
}

void Player::OnCollision(Actor* actor)
{

	return;

	if (dynamic_cast<Enemy*>(actor))
	{
		destroy = true;
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::white, 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes I'm dead");
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}
}