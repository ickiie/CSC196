#pragma once
#include "Engine.h"

class Game {

public:
	enum class eState {

		Title,
		StartGame,
		StartLevel,
		Game,
		StartLevel2,
		Level2,
		StartLevel3,
		Level3,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void UpdateStartLevel2(float dt);
	void UpdateStartLevel3(float dt);
	
	void OnAddPoints(const nc::Event& event);
	void OnPlayerDamaged(const nc::Event& event);
	void OnGunPowerup(const nc::Event& event);
	void OnFrPowerup(const nc::Event& event);
	void OnHealer(const nc::Event& event);

public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;
	
private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game::* stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t health = 3;
	size_t gunLevel = 1;
	size_t frLevel = 1;
};