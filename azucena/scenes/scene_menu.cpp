#include "scene_menu.h"
#include "controls_map.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
#if DEBUG
  cout << "Menu Load \n";
#endif
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Platformer\nPress Space to Start");
  }

	// Initialise keys
	GameKey key;
	key.inputType = KeyboardInput;
	key.eventType = sf::Event::KeyPressed;
	key.keyCode = sf::Keyboard::Space;
	//Controls::Keys["Enter"] = key;
	Controls::GetKeys()["Enter"] = key;

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {

	//if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
	//if (Controls::testEvent(Controls::Keys["Enter"], Engine::GetEvent())) {
	if (Controls::testEvent(Controls::GetKeys()["Enter"], Engine::GetEvent())) {
		Engine::ChangeScene(&level1);
	}

  Scene::Update(dt);
}
