#include "scene_menu.h"
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
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}
