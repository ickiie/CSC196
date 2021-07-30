#include "gunPowerup.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void gunPowerup::Update(float dt) {
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) {
		destroy = true;
	}

}

void gunPowerup::OnCollision(Actor* actor) {


	if (dynamic_cast<Player*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")) {
		Player* player = scene->GetActor<Player>();
		player->gunPowerup();
		destroy = true;
		
		//particle
		//audio

		nc::Event event;
		event.name = "gunPickup";
		event.data = 1;
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}

}
