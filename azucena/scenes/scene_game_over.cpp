#include "scene_game_over.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include "../controls.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

float timer_before_can_change_scene = 2.0;
shared_ptr<Entity> txt_return_to_menu;

void GameOverScene::Load()
{
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>("Game over");
    t->getText()->setCharacterSize(40.0f);
    t->getText()->setOrigin(t->getText()->getLocalBounds().width / 2, t->getText()->getLocalBounds().height / 2);
    txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, ((float)Engine::GetWindow().getSize().y / 2) - 40.0f });
  }

  {
    txt_return_to_menu.reset();
    txt_return_to_menu = makeEntity();
    auto t = txt_return_to_menu->addComponent<TextComponent>("Press \"Sprint\" to return to menu.");
    txt_return_to_menu->setPosition({ (float)Engine::GetWindow().getSize().x / 2, ((float)Engine::GetWindow().getSize().y / 2) + 10.0f });
    txt_return_to_menu->setVisible(false);
  }

  // Set view
  Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

  setLoaded(true);
}

void GameOverScene::Update(const double& dt)
{
  timer_before_can_change_scene -= dt;

  if (timer_before_can_change_scene <= 0.0f)
  {
    if (!txt_return_to_menu->isVisible()) txt_return_to_menu->setVisible(true);

    if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Return to menu")) ||
      Keyboard::isKeyPressed(Controls::GetKeyboardKey("Sprint")) ||
      Keyboard::isKeyPressed(Controls::GetKeyboardKey("Shoot")))
    {
      Engine::ChangeScene((Scene*)&scene_menu);
    }
  }

  Scene::Update(dt);
}