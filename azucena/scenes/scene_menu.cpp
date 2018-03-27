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
        "Azucena\nPress Space to Start");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (float)Engine::GetWindow().getSize().y / 2 });
  }

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Controls::GetKeyboardKey("Enter"))) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}
