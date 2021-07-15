#include "Scene.h"
#include "Actor.h"

namespace nc
{
	void Scene::Update(float dt)
	{
		for (auto& actor : actors)
		{
			actor->Update(dt);
		}

		auto iter = actors.begin();
		while (iter != actors.end()) {

			if ((*iter)->destroy) {

				iter = actors.erase(iter);
			}
			else {

				iter++;
			}
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (auto& actor : actors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor.get()->scene = this;
		actors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor) {

	}

	void Scene::RemoveAllActors() {
		actors.clear();
	}
}
