#pragma once
#include "Base/Actor.h"

class Player : public nc::Actor {

public:
	Player(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

	void gunPowerup();
	void frPowerup();
	void Healer();

private:
	float fireTimer{ 0 };
	float fireRate{ 1.0f };
	float speed{ 300 };
	nc::Vector2 velocity;


	void gunPowerup1();
	void gunPowerup2();
	void gunPowerup3();

};