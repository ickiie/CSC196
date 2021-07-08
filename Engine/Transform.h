#pragma once
#include "Math/Vector2.h"
#include <vector>

namespace nc {


	struct Transform {

		Vector2 position;
		float rotation = 0;
		float scale = 1;

		Transform() {}
		Transform(const Vector2 position, float rotation = 0, float scale = 1) : position{ position }, rotation{rotation}, scale{scale} {}
	};
}