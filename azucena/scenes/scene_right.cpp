#include "scene_right.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include "../controls.h"
#include "../prefabs.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_player_health.h"

using namespace std;
using namespace sf;

void RightScene::Load()
{
	ls::loadLevelFile("res/level_right.txt", 32.0f);

	// Create player
	_player = create_player();

	// Create enemies
	create_enemies();

	// Add physics colliders to level tiles.
	add_physics_colliders_to_tiles();

	// Add key and door
	if (!Data::door_right_opened)
	{
		_door = create_door();
		create_key();
	}

	// Create main collectible
	create_baby_llama(1);

	// Add UI
	create_game_ui();

	// Set view
	_view_center = _player->getPosition();

	// Music
	_music_overworld = Resources::get<Music>("overworld.wav");
	_music_overworld->play();
	_music_overworld->setLoop(true);

	setLoaded(true);
}

void RightScene::UnLoad() {
	_player.reset();
	_door.reset();
	_music_overworld->stop();
	_music_overworld.reset();
	ls::unload();
	Scene::UnLoad();
}

void RightScene::Update(const double& dt) {

	// Camera follows player
	// REMEMBER TO PUT THIS BEFORE YOU CHECK FOR CHANGING SCENE
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	float view_player_distance = sqrt(((_player->getPosition().x - _view_center.x) * (_player->getPosition().x - _view_center.x)) + ((_player->getPosition().y - _view_center.y) * (_player->getPosition().y - _view_center.y)));
	if (view_player_distance > 80.0f)
		_view_center += (_player->getPosition() - _view_center) * (float)dt * 2.3f;
	view.setCenter(_view_center);

	Engine::GetWindow().setView(view);

	// Save door as opened
	if (!Data::door_right_opened)
	{
		if (_door->get_components<StateMachineComponent>()[0]->currentState() == "open")
		{
			Data::door_right_opened = true;
		}
	}

	// Game over
	bool flag_game_over = false;
	if (_player->get_components<PlayerHealthComponent>()[0]->getHealth() <= 0) flag_game_over = true;

	// Exits
	bool flag_exit_1 = false;
	if (ls::getTileAt(_player->getPosition()) == ls::EXIT_1) flag_exit_1 = true;

	// Press Esc for 1 sec button to return to menu
	bool flag_menu = false;
	if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu"))) _escButtonTimePressed += dt;
	else _escButtonTimePressed = 0.0f;
	if (_escButtonTimePressed > 1.0f) flag_menu = true;

	// Change scene
	if (flag_game_over) Engine::ChangeScene((Scene*)&scene_game_over);
	else if (flag_exit_1) Engine::ChangeScene((Scene*)&scene_center);
	else if (flag_menu) Engine::ChangeScene((Scene*)&scene_menu);

	Scene::Update(dt);
}

void RightScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
