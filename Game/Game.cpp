#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"
#include "Actors/gunPowerup.h"
#include "Actors/frPowerup.h"
#include "Actors/Healer.h"

void Game::Initialize() {

	engine = std::make_unique<nc::Engine>();
	engine->Startup();
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("Plaser", "Plaser.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("Elaser", "ELaser.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerDamaged", std::bind(&Game::OnPlayerDamaged, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("gunPickup", std::bind(&Game::OnGunPowerup, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("frPickup", std::bind(&Game::OnFrPowerup, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("Healer", std::bind(&Game::OnHealer, this, std::placeholders::_1));

	//stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown() {

	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt) {

	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE)) {

			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame: {
		score = 0;
		health = 10;
		gunLevel = 1;
		state = eState::StartLevel;
		break;
	}
	case Game::eState::StartLevel: {

		UpdateStartLevel(dt);
		state = eState::Game;
		break;
	}
	case Game::eState::Game: {
		if (scene->GetActors<Enemy>().size() == 0) {
			state = eState::StartLevel2;
		}
		break;
	}
	case Game::eState::StartLevel2: {
		
		UpdateStartLevel2(dt);
		state = eState::Level2;
	}
	case Game::eState::Level2: {
		if (scene->GetActors<Enemy>().size() == 0) {
			state = eState::StartLevel3;
		}
		break;
	}
	case Game::eState::StartLevel3: {

		UpdateStartLevel3(dt);
		state = eState::Level3;
	}
	case Game::eState::Level3: {
		if (scene->GetActors<Enemy>().size() == 0) {
			state = eState::StartLevel2;
		}
		break;
	}
	case Game::eState::GameOver:
		scene->RemoveAllActors();
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics) {

	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(360, 300 + static_cast<int>(std::sin(stateTimer * 6.0f) * 10.0f), "VECTREX");
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(340, 360, "Press Space to Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::StartLevel2:
		break;
	case Game::eState::Level2:
		break;
	case Game::eState::StartLevel3:
		break;
	case Game::eState::Level3:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(350, 370, "Game Over");
		graphics.DrawString(350, 400, "Final Score:");
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(350, 430, std::to_string(score).c_str());
		
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(health).c_str());
	graphics.DrawString(750, 550, std::to_string(gunLevel).c_str());
	graphics.DrawString(680, 550, "GUN STAT:");
	graphics.DrawString(750, 525, std::to_string(frLevel).c_str());
	graphics.DrawString(680, 525, "FIRE RATE:");
	graphics.DrawString(680, 20, "HEALTH:");


	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE)) {

		stateFunction = &Game::UpdateStartLevel;
		state = eState::StartGame;
	}
}

void Game::UpdateStartLevel(float dt)
{
	scene->AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 3.0f), engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("shape.txt"), 300.0f));
	for (size_t i = 0; i < 4; i += 1) {

		scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("enemy.txt"), 100.0f));
	}

	for (size_t i = 0; i < 1; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 80) {
			scene->AddActor(std::make_unique<gunPowerup>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("gunPowerup.txt")));
		}
	}

	for (size_t i = 0; i < 2; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 50) {
			scene->AddActor(std::make_unique<frPowerup>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("frPowerup.txt")));
		}
	}

	for (size_t i = 0; i < 1; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 50) {
			scene->AddActor(std::make_unique<Healer>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("bomb.txt")));
		}
	}

}

void Game::UpdateStartLevel2(float dt)
{
	for (size_t i = 0; i < 6; i += 1) {

		scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("enemy.txt"), 100.0f));
	}

	for (size_t i = 0; i < 1; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 80) {
			scene->AddActor(std::make_unique<gunPowerup>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("gunPowerup.txt")));
		}
	}

	for (size_t i = 0; i < 2; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 50) {
			scene->AddActor(std::make_unique<frPowerup>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("frPowerup.txt")));
		}
	}

	for (size_t i = 0; i < 1; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 50) {
			scene->AddActor(std::make_unique<Healer>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("bomb.txt")));
		}
	}

}

void Game::UpdateStartLevel3(float dt)
{
	for (size_t i = 0; i < 2; i += 1) {

		scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("enemy.txt"), 100.0f));
	}

	for (size_t i = 0; i < 1; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 80) {
			scene->AddActor(std::make_unique<gunPowerup>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("gunPowerup.txt")));
		}
	}

	for (size_t i = 0; i < 2; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 50) {
			scene->AddActor(std::make_unique<frPowerup>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("frPowerup.txt")));
		}
	}

	for (size_t i = 0; i < 1; i += 1) {
		int x = nc::RandomRange(1, 100);
		if (x >= 50) {
			scene->AddActor(std::make_unique<Healer>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 2.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("bomb.txt")));
		}
	}
}

void Game::OnAddPoints(const nc::Event& event) {

	score += std::get<int>(event.data);
}

void Game::OnPlayerDamaged(const nc::Event& event)
{
	std::cout << "damage\n";
	health -= 1;
	if (health <= 0) {
		state = eState::GameOver;
	}

}

void Game::OnGunPowerup(const nc::Event& event) {
	if (gunLevel < 4) {
		gunLevel += 1;
	}
}

void Game::OnFrPowerup(const nc::Event& event) {
	frLevel += 1;
}

void Game::OnHealer(const nc::Event& event) {

	health = 10;
}

