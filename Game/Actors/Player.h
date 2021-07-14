#pragma once
#include "Base/Actor.h"

class Player : public nc::Actor {

public:
	Player(const nc::Transform& transform, nc::Shape* shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;

private:
	float speed{ 300 };
};