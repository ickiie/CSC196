#pragma once
#include "Object.h"
#include "Transform.h"
#include "core.h"

namespace nc {

	class Shape;

	class Actor : public Object {

	public:
		Actor(const Transform& transform, Shape* shape) : transform{transform}, shape{shape} {}

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

	public:
		Transform transform;
		Shape* shape;
	};
}