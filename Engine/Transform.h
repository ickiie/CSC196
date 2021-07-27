#pragma once
#include "Math/Vector2.h"
#include "Math/Matrix22.h"

namespace nc {


	struct Transform {

		Vector2 position;
		float rotation = 0;
		float scale = 1;

		Matrix22 matrix;

		Transform() {}
		Transform(const Vector2 position, float rotation = 0, float scale = 1) : position{ position }, rotation{rotation}, scale{scale} {}

		void Update();
	};
}