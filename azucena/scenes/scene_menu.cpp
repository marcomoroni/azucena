#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../constrols.h"

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

	// Set controls
	Controls::SetKeyboardKey("Enter", Keyboard::Space);
	Controls::SetKeyboardKey("Sprint", Keyboard::Space);
	Controls::SetKeyboardKey("Up", Keyboard::W);
	Controls::SetKeyboardKey("Down", Keyboard::S);
	Controls::SetKeyboardKey("Left", Keyboard::A);
	Controls::SetKeyboardKey("Right", Keyboard::D);

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Controls::GetKeyboardKey("Enter"))) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}
