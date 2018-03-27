#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../constrols.h"
#include "../prefabs.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_Start;
shared_ptr<Entity> btn_Quit;

void MenuScene::Load() {
#if DEBUG
  cout << "Menu Load \n";
#endif
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>("Azucena");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
  }

	btn_Start = create_button("Start");
	btn_Start->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 200.0f });

	btn_Quit = create_button("Quit");
	btn_Quit->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 300.0f });

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {

	if (btn_Start->get_components<ButtonComponent>()[0]->isSelected())
	{
		Engine::ChangeScene(&level1);
	}

	if (btn_Quit->get_components<ButtonComponent>()[0]->isSelected())
	{
		Engine::GetWindow().close();
	}

  Scene::Update(dt);
}
