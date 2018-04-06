#include "scene_center.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include "../constrols.h"
#include "../prefabs.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_player_health.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
shared_ptr<Entity> door;
Vector2f view_center;
float _escButtonTimePressed = 0.0f;

void CenterScene::Load()
{
  ls::loadLevelFile("res/level_1.txt", 32.0f);

  // Create player
	player = create_player();

	// Create enemies
	create_enemies();

  // Add physics colliders to level tiles.
	add_physics_colliders_to_tiles();

  // Add key and door
  if (!Data::door_right_opened)
  {
    door = create_door();
    create_key();
  }

  // Create main collectibles
  create_baby_llama(1);

	// Add UI
	create_game_ui();

	// Set view
	view_center = player->getPosition();

  setLoaded(true);
}

void CenterScene::UnLoad() {
  player.reset();
  door.reset();
  ls::unload();
  Scene::UnLoad();
}

void CenterScene::Update(const double& dt) {

  // Note: Scenes should be changed at the very end, because the update will
  // keep running even if the scene is unloaded. If this happenes, you cannot
  // use any of the entities or variable of the scene.
  // There are flags to keep track if the scene has to be changed and they will
  // used at the end of the function.

	// Camera follows player
	// REMEMBER TO PUT THIS BEFORE YOU CHECK FOR CHANGING SCENE
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	float view_player_distance = sqrt(((player->getPosition().x - view_center.x) * (player->getPosition().x - view_center.x)) + ((player->getPosition().y - view_center.y) * (player->getPosition().y - view_center.y)));
	if (view_player_distance > 80.0f)
		view_center += (player->getPosition() - view_center) * (float)dt * 2.3f;
	view.setCenter(view_center);
	
	Engine::GetWindow().setView(view);

  // Save door as opened
  if (!Data::door_right_opened)
  {
    if (door->get_components<StateMachineComponent>()[0]->currentState() == "open")
    {
      Data::door_right_opened = true;
    }
  }

  // Game over
  bool flag_game_over = false;
  if (player->get_components<PlayerHealthComponent>()[0]->getHealth() <= 0) flag_game_over = true;

  // Exits
  bool flag_exit_1 = false;
  if (ls::getTileAt(player->getPosition()) == ls::EXIT_1) flag_exit_1 = true;

	// Press Esc for 1 sec button to return to menu
  bool flag_menu = false;
  if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu"))) _escButtonTimePressed += dt;
	else _escButtonTimePressed = 0.0f;
  if (_escButtonTimePressed > 1.0f) flag_menu = true;

  // Change scene
  if (flag_game_over) Engine::ChangeScene((Scene*)&game_over);
  else if (flag_exit_1) Engine::ChangeScene((Scene*)&menu); // temporary /////////////////
  else if (flag_menu) Engine::ChangeScene((Scene*)&menu);

  Scene::Update(dt);
}

void CenterScene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
