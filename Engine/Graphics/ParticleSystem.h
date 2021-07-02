#pragma once
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include <vector>


namespace nc {

	struct Particle {

		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		Color color;
		float lifetime;
		bool isActive{ false };

		static bool isNotActive(Particle particle) { return particle.isActive == false; }
	};

	class ParticleSystem {

	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position, size_t count, float lifetime, const Color& color, float speed);

	private:
		std::vector<Particle> particles;
	};
}
