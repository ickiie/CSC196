#include "Enemy.h"
#include "Mathutils.h"

void Enemy::Update(float dt) {
	
	Actor::Update(dt);
			
	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
}