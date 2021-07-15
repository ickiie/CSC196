#pragma once
#include "Object.h"
#include "Transform.h"
#include "core.h"
#include <memory>

namespace nc {

	class Shape;
	class Scene;

	class Actor : public Object {

	public:
		Actor(const Transform& transform, std::shared_ptr<Shape> shape) : transform{transform}, shape{ shape } {}

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

	public:
		bool destroy;

		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene{ nullptr };
	};
}