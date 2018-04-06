#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../prefabs.h"
#include "../components/cmp_button.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_Start;
shared_ptr<Entity> btn_Continue;
shared_ptr<Entity> btn_Load;
shared_ptr<Entity> btn_Options;
shared_ptr<Entity> btn_Quit;

void MenuScene::Load() {

  Resources::load<Texture>("tex.png");

#if DEBUG
  cout << "Menu Load \n";
#endif
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>("Azucena");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
  }

  btn_Start.reset();
	btn_Start = create_button("New game");
	btn_Start->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 200.0f });

  btn_Continue.reset();
  btn_Continue = create_button("Continue");
  btn_Continue->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 240.0f });

  btn_Load.reset();
  btn_Load = create_button("Load");
  btn_Load->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 280.0f });

  btn_Options.reset();
	btn_Options = create_button("Options");
	btn_Options->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 320.0f });

  btn_Quit.reset();
	btn_Quit = create_button("Save and quit");
	btn_Quit->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 360.0f });

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {

	if (btn_Start->get_components<ButtonComponent>()[0]->isSelected())
	{
    Data::reset();
		Engine::ChangeScene(&center);
	}

  if (btn_Continue->get_components<ButtonComponent>()[0]->isSelected())
  {
    Engine::ChangeScene(&center);
  }

  if (btn_Load->get_components<ButtonComponent>()[0]->isSelected())
  {
    Data::load();
    Engine::ChangeScene(&center);
  }

	if (btn_Options->get_components<ButtonComponent>()[0]->isSelected())
	{
		Engine::ChangeScene(&options);
	}

	if (btn_Quit->get_components<ButtonComponent>()[0]->isSelected())
	{
    Data::save();
		Engine::GetWindow().close();
	}

  Scene::Update(dt);
}
