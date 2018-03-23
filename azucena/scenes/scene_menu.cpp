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

	// Set view
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Controls::GetKeyboardKey("Enter"))) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}
