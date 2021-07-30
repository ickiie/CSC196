#include "Player.h"
#include "Projectile.h"
#include "Engine.h"
#include "Enemy.h"
#include <memory>

float dampning;

int placeholder = 1;

int gp1;
int gp2;
int gp3;
int gunStat = 1;

Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {

}

void Player::Initialize() {

	std::unique_ptr additionThing = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("added.txt"));
	additionThing->transform.localPosition = nc::Vector2{ 0, 0 };
	AddChild(std::move(additionThing));

	/*std::unique_ptr newgun = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("newgun.txt"));
	newgun->transform.localPosition = nc::Vector2{ -8, -10 };
	AddChild(std::move(newgun));

	std::unique_ptr newgun2 = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("newgun.txt"));
	newgun2->transform.localPosition = nc::Vector2{ 8, -10 };
	AddChild(std::move(newgun2));

	std::unique_ptr newgun3 = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("newgun.txt"));
	newgun3->transform.localPosition = nc::Vector2{ 0, -14 };
	AddChild(std::move(newgun3));*/

	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ -8, 0 };
	locator->transform.localRotation = nc::DegToRad(90);
	AddChild(std::move(locator));

}

void Player::Update(float dt) {

	Actor::Update(dt);

	//movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	if (Core::Input::IsPressed('S')) dampning = 0.97f;
	if (!Core::Input::IsPressed('S')) dampning = 0.99f;
	if (Core::Input::IsPressed('S')) thrust = -speed/2;


	nc::Vector2 acceleration;
	acceleration += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * thrust * dt;
	//nc::Vector2 gravity = (nc::Vector2{ 400, 300 } - transform.position).Normalized() * 50;
	//nc::Vector2 gravity = nc::Vector2::down * 50;
	//acceleration += gravity;


	velocity += acceleration * dt;
	transform.position += velocity * 100.0f * dt;

	velocity *= dampning; //damping
 
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	// fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {

		fireTimer = fireRate;
		
		nc::Transform t = children[0]->transform;
		t.scale = 0.5f;

		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("elaser.txt"), 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));

		if (gunStat >= 2) {
			nc::Transform x = children[gp1]->transform;
			x.scale = 0.5f;

			std::unique_ptr<Projectile> projectile2 = std::make_unique<Projectile>(x, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("elaser.txt"), 600.0f);
			projectile2->tag = "Player";
			scene->AddActor(std::move(projectile2));
		}

		if (gunStat >= 3) {
			nc::Transform y = children[gp2]->transform;
			y.scale = 0.5f;

			std::unique_ptr<Projectile> projectile3 = std::make_unique<Projectile>(y, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("elaser.txt"), 600.0f);
			projectile3->tag = "Player";
			scene->AddActor(std::move(projectile3));
		}

		if (gunStat >= 4) {
			nc::Transform z = children[gp3]->transform;
			z.scale = 0.5f;

			std::unique_ptr<Projectile> projectile4 = std::make_unique<Projectile>(z, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("elaser.txt"), 600.0f);
			projectile4->tag = "Player";
			scene->AddActor(std::move(projectile4));
		}

		scene->engine->Get<nc::AudioSystem>()->PlayAudio("Plaser");
	}


	std::vector<nc::Color> colors = { nc::Color::black, nc::Color::red };
	if (!Core::Input::IsPressed('W')) scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 2, 1, colors, 50, nc::DegToRad(270), nc::DegToRad(35));
	if (Core::Input::IsPressed('W')) scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 3, colors, 50, nc::DegToRad(270), nc::DegToRad(90));
}

void Player::OnCollision(Actor* actor)
{

	//return;

	if (dynamic_cast<Enemy*>(actor))
	{
		//destroy = true;
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::white, 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "PlayerDamaged";
		event.data = 1;
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag != "Player")
	{
		actor->destroy = true;
		//destroy = true;
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::white, 50);
		//scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "PlayerDamaged";
		event.data = 1;
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}
}

void Player::gunPowerup()
{
	std::cout << "powerup\n";
	
	if (gunStat == 1) {
		gunPowerup1();
		return;
	}
	if (gunStat == 2) {
		gunPowerup2();
		return;
	}
	if (gunStat == 3) {
		gunPowerup3();
		return;
	}
	if (gunStat == 4) {
		return;
	}
	/*gunPowerup1();
	gunPowerup2();
	gunPowerup3();*/
}

void Player::frPowerup() {

	if (fireRate > 0.2f) {
		fireRate -= 0.1f;

		nc::Event event;
		event.name = "frPickup";
		event.data = 1;
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}


}

void Player::Healer() {

	nc::Event event;
	event.name = "Healer";
	event.data = 1;
	scene->engine->Get<nc::EventSystem>()->Notify(event);
}



void Player::gunPowerup1() {
	gunStat++;

	std::unique_ptr newgun = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("newgun.txt"));
	newgun->transform.localPosition = nc::Vector2{ 2, -10 };
	AddChild(std::move(newgun));

	placeholder++;
	gp1 = placeholder;

}

void Player::gunPowerup2() {
	gunStat++;

	std::unique_ptr newgun2 = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("newgun.txt"));
	newgun2->transform.localPosition = nc::Vector2{ 2, 10 };
	AddChild(std::move(newgun2));

	placeholder++;
	gp2 = placeholder;

}

void Player::gunPowerup3() {
	gunStat++;

	std::unique_ptr newgun3 = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("newgun.txt"));
	newgun3->transform.localPosition = nc::Vector2{ -12, 0 };
	AddChild(std::move(newgun3));

	placeholder++;
	gp3 = placeholder;

}