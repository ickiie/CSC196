#pragma once
#include "Base/Actor.h"

class Healer : public nc::Actor {

public:
	Healer(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape) : nc::Actor{ transform, shape } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float lifetime{ 10 };


};
