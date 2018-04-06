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

void MenuScene::Load() {

  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>("Azucena");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
  }

  _btn_Start.reset();
	_btn_Start = create_button("New game");
	_btn_Start->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 200.0f });

  _btn_Continue.reset();
  _btn_Continue = create_button("Continue");
  _btn_Continue->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 240.0f });

  _btn_Load.reset();
  _btn_Load = create_button("Load");
  _btn_Load->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 280.0f });

  _btn_Options.reset();
	_btn_Options = create_button("Options");
	_btn_Options->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 320.0f });

  _btn_Quit.reset();
	_btn_Quit = create_button("Save and quit");
	_btn_Quit->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 360.0f });

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {

	if (_btn_Start->get_components<ButtonComponent>()[0]->isSelected())
	{
    Data::reset();
		Engine::ChangeScene(&scene_center);
	}

  if (_btn_Continue->get_components<ButtonComponent>()[0]->isSelected())
  {
    Engine::ChangeScene(&scene_center);
  }

  if (_btn_Load->get_components<ButtonComponent>()[0]->isSelected())
  {
    Data::load();
    Engine::ChangeScene(&scene_center);
  }

	if (_btn_Options->get_components<ButtonComponent>()[0]->isSelected())
	{
		Engine::ChangeScene(&scene_options);
	}

	if (_btn_Quit->get_components<ButtonComponent>()[0]->isSelected())
	{
    Data::save();
		Engine::GetWindow().close();
	}

  Scene::Update(dt);
}
