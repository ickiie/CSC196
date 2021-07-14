#include "Scene.h"
#include "Actor.h"

namespace nc
{
	void Scene::Update(float dt)
	{
		for (Actor* actor : actors)
		{
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (Actor* actor : actors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor)
	{
		actors.push_back(actor);
	}
}
