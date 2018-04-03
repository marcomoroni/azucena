#include "scene_level1.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <system_resources.h>
#include "../constrols.h"
#include "../prefabs.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
Vector2f view_center;
float _escButtonTimePressed = 0.0f;

void Level1Scene::Load() {
#if DEBUG
  cout << " Scene 1 Load" << endl;
#endif
  ls::loadLevelFile("res/level_1.txt", 32.0f);

  // Create player
	player = create_player();

	// Create enemies
	create_enemies();

  // Add physics colliders to level tiles.
	add_physics_colliders_to_tiles();

  // Add key
  create_key();
  create_door();

	// Add UI
	create_game_ui();

	// Set view
	view_center = player->getPosition();

#if DEBUG
  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;
#endif

  setLoaded(true);
}

void Level1Scene::UnLoad() {
#if DEBUG
  cout << "Scene 1 Unload" << endl;
#endif
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	// Camera follows player
	// REMEMBER TO PUT THIS BEFORE YOU CHECK FOR CHANGING SCENE
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	float view_player_distance = sqrt(((player->getPosition().x - view_center.x) * (player->getPosition().x - view_center.x)) + ((player->getPosition().y - view_center.y) * (player->getPosition().y - view_center.y)));
	if (view_player_distance > 80.0f)
		view_center += (player->getPosition() - view_center) * (float)dt * 2.3f;
	view.setCenter(view_center);
	
	Engine::GetWindow().setView(view);

  // Exits
  if (ls::getTileAt(player->getPosition()) == ls::EXIT_1) {
    Engine::ChangeScene((Scene*)&level2);
  }

	// Press Esc for 1 sec button to return to menu
	if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu"))) _escButtonTimePressed += dt;
	else _escButtonTimePressed = 0.0f;
	if (_escButtonTimePressed > 1.0f) Engine::ChangeScene((Scene*)&menu);

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
