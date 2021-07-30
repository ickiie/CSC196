#include "frPowerup.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void frPowerup::Update(float dt) {
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) {
		destroy = true;
	}

}

void frPowerup::OnCollision(Actor* actor) {


	if (dynamic_cast<Player*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")) {
		Player* player = scene->GetActor<Player>();
		player->frPowerup();
		destroy = true;

		//particle
		//audio

	}

}
