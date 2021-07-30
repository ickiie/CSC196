#pragma once
#include "Base/Actor.h"

class gunPowerup : public nc::Actor {

public:
	gunPowerup(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape) : nc::Actor{ transform, shape } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float lifetime{ 10 };


};
