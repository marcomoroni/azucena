#include "scene_center.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include "../controls.h"
#include "../prefabs.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_player_health.h"
#include "../components/cmp_player_controls.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_game_ui.h"

using namespace std;
using namespace sf;

void CenterScene::Load()
{
	ls::loadLevelFile("res/level_center.txt", 32.0f);

	// Create player
	_player = create_player();
	// Restore health
	auto h = _player->get_components<PlayerHealthComponent>()[0];
	h->setHealth(h->getMaxHealth());

	// Create enemies
	create_enemies();

	// Create main collectible
	if (Data::main_collectible_right || !Data::introPlayed)
	{
		_baby1 = create_baby_llama(1);
		_baby1->get_components<StateMachineComponent>()[0]->changeState("idle");
	}
	if (Data::main_collectible_top || !Data::introPlayed)
	{
		_baby2 = create_baby_llama(2);
		_baby2->get_components<StateMachineComponent>()[0]->changeState("idle");
	}
	if (Data::main_collectible_left || !Data::introPlayed)
	{
		_baby3 = create_baby_llama(3);
		_baby3->get_components<StateMachineComponent>()[0]->changeState("idle");
	}

	// Add physics colliders to level tiles.
	create_walls();

	// Add UI
	create_game_ui();

	// For intro cutscene
	if (!Data::introPlayed)
	{
		{
			_zzz = makeEntity();
			auto s = _zzz->addComponent<SpriteComponent>();
			auto tex = Resources::get<Texture>("tex.png");
			s->setTexture(tex);
			s->getSprite().setTextureRect(IntRect(32 * 5, 32 * 5, 32, 32));
			s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
			_zzz->setVisible(false);
		}

		{
			_ohmy = makeEntity();
			auto s = _ohmy->addComponent<SpriteComponent>();
			auto tex = Resources::get<Texture>("tex.png");
			s->setTexture(tex);
			s->getSprite().setTextureRect(IntRect(32, 32 * 2, 32, 32));
			s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
			_ohmy->setVisible(false);
		}
	}

	// Set view
	_view_center = _player->getPosition();

	setLoaded(true);
}

void CenterScene::UnLoad() {
	_player.reset();
	_baby1.reset();
	_baby2.reset();
	_baby3.reset();
	_zzz.reset();
	_ohmy.reset();
	ls::unload();
	Scene::UnLoad();
}

void CenterScene::Update(const double& dt) {

	// Note: Scenes should be changed at the very end, because the update will
	// keep running even if the scene is unloaded. If this happenes, you cannot
	// use any of the entities or variable of the scene.
	// There are flags to keep track if the scene has to be changed and they will
	// used at the end of the function.

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));

	// Intro cutscene /////////////////////
	if (!Data::introPlayed)
	{
		_intoTime += dt;

		view.zoom(0.8f);
		_player->get_components<PlayerControlsComponent>()[0]->setCanMove(false);

		// Baby llamas move
		float speed = 200.0f;
		if (_intoTime > 4.0f)
		{
			_baby1->get_components<PhysicsComponent>()[0]->teleport(_baby1->getPosition() + (Vector2f(1.0f, 0.0f) * speed * (float)dt));
		}
		if (_intoTime > 5.4f)
		{
			_baby2->get_components<PhysicsComponent>()[0]->teleport(_baby2->getPosition() + (Vector2f(0.0f, -1.0f) * speed * (float)dt));
		}
		if (_intoTime > 4.2f)
		{
			_baby3->get_components<PhysicsComponent>()[0]->teleport(_baby3->getPosition() + (Vector2f(-1.0f, 0.0f) * speed * (float)dt));
		}

		// Babies disappear
		if (_baby1->isVisible() && ls::getTileAt(_baby1->getPosition()) == ls::EXIT_1)
		{
			_baby1->setVisible(false);
		}
		if (_baby2->isVisible() && ls::getTileAt(_baby2->getPosition()) == ls::EXIT_2)
		{
			_baby2->setVisible(false);
		}
		if (_baby3->isVisible() && ls::getTileAt(_baby3->getPosition()) == ls::EXIT_3)
		{
			_baby3->setVisible(false);
		}

		// Azucena ZZZ
		if (_intoTime < 7.0f)
		{
			_zzz->setVisible(true);
			_zzz->setPosition(_player->getPosition() + Vector2f(0.0f, (int)(_intoTime * 2) % 2 == 0 ? -40.0f : -44.0f));
		}
		else
		{
			_zzz->setVisible(false);
		}

		// Azucena ohmy
		if (_intoTime > 8.0f && _intoTime < 8.4f)
		{
			//_ohmy->setVisible(true);
			_ohmy->setPosition(_player->getPosition() + Vector2f(0.0f, -32.0f));
			_ohmy->setVisible((int)(_intoTime * 10) % 2 == 0 ? true : false);
		}
		else
		{
			_ohmy->setVisible(false);
		}

		// End cutscene
		if (_intoTime > 9.0f)
		{
			_baby1->setPosition({ -100.0f, -100.0f });
			_baby2->setPosition({ -100.0f, -100.0f });
			_baby3->setPosition({ -100.0f, -100.0f });
			Data::introPlayed = true;

			// Show controls string
			if (!Data::messageShown_basicControls)
			{
				Engine::GetActiveScene()->ents.find("game ui")[0]->get_components<GameUIComponent>()[0]->showBottomMessage(0);
				Data::messageShown_basicControls = true;
			}
		}
	}
	else
	{
		_player->get_components<PlayerControlsComponent>()[0]->setCanMove(true);
	}
	///////////////////////////////////////

	// Camera follows player
	// REMEMBER TO PUT THIS BEFORE YOU CHECK FOR CHANGING SCENE
	float view_player_distance = sqrt(((_player->getPosition().x - _view_center.x) * (_player->getPosition().x - _view_center.x)) + ((_player->getPosition().y - _view_center.y) * (_player->getPosition().y - _view_center.y)));
	if (view_player_distance > 80.0f)
		_view_center += (_player->getPosition() - _view_center) * (float)dt * 2.3f;
	view.setCenter(_view_center);

	Engine::GetWindow().setView(view);

	// Show rewards messages
	if (Data::main_collectible_right && !Data::messageShown_useHealingHerb)
	{
		Engine::GetActiveScene()->ents.find("game ui")[0]->get_components<GameUIComponent>()[0]->showBottomMessage(4);
		Data::messageShown_useHealingHerb = true;
	}
	if (Data::main_collectible_left && !Data::messageShown_rewardSpit)
	{
		Engine::GetActiveScene()->ents.find("game ui")[0]->get_components<GameUIComponent>()[0]->showBottomMessage(5);
		Data::messageShown_rewardSpit = true;
	}
	if (Data::main_collectible_top && !Data::messageShown_rewardHealth)
	{
		Engine::GetActiveScene()->ents.find("game ui")[0]->get_components<GameUIComponent>()[0]->showBottomMessage(3);
		Data::messageShown_rewardHealth = true;
	}

	// Game over
	bool flag_game_over = false;
	if (_player->get_components<PlayerHealthComponent>()[0]->getHealth() <= 0) flag_game_over = true;

	// Exits
	bool flag_exit_1 = false;
	if (ls::getTileAt(_player->getPosition()) == ls::EXIT_1) flag_exit_1 = true;
	bool flag_exit_2 = false;
	if (ls::getTileAt(_player->getPosition()) == ls::EXIT_2) flag_exit_2 = true;
	bool flag_exit_3 = false;
	if (ls::getTileAt(_player->getPosition()) == ls::EXIT_3) flag_exit_3 = true;

	// Press Esc for 1 sec button to return to menu
	bool flag_menu = false;
	if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu"))) _escButtonTimePressed += dt;
	else _escButtonTimePressed = 0.0f;
	if (_escButtonTimePressed > 1.0f) flag_menu = true;

	// Change scene
	if (flag_game_over) Engine::ChangeScene((Scene*)&scene_game_over);
	else if (flag_exit_1) Engine::ChangeScene((Scene*)&scene_right);
	else if (flag_exit_2) Engine::ChangeScene((Scene*)&scene_top);
	else if (flag_exit_3) Engine::ChangeScene((Scene*)&scene_left);
	else if (flag_menu) Engine::ChangeScene((Scene*)&scene_menu);

	Scene::Update(dt);
}

void CenterScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
