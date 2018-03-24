#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../constrols.h"
#include "../entities_creator.h"

using namespace std;
using namespace sf;

void MenuScene::Load() {
#if DEBUG
  cout << "Menu Load \n";
#endif
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>("Azucena");
		t->getText().setOrigin(t->getText().getLocalBounds().width / 2, t->getText().getLocalBounds().height / 2);
		txt->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
  }

	{
		auto b = create_button("Start");
		b->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 250.f));
	}

	{
		auto b = create_button("Options");
		b->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 350.f));
	}

	{
		auto b = create_button("Quit");
		b->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 450.f));
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
