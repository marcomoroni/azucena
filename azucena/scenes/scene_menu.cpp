#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../prefabs.h"
#include "../components/cmp_button.h"
#include "system_resources.h"
#include "SFML/Graphics.hpp" // include to use events

using namespace std;
using namespace sf;

void MenuScene::Load() {

	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Azucena");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
		t->getText()->setColor(Color(233, 219, 204));
	}

	_btns.clear();

	_btn_Start.reset();
	_btn_Start = create_button("New game");
	_btns.push_back(_btn_Start);

	_btn_Continue.reset();
	_btn_Continue = create_button("Continue");
	_btns.push_back(_btn_Continue);

	_btn_Load.reset();
	_btn_Load = create_button("Load");
	_btns.push_back(_btn_Load);

	_btn_Options.reset();
	_btn_Options = create_button("Options");
	_btns.push_back(_btn_Options);

	_btn_Quit.reset();
	_btn_Quit = create_button("Save and quit");
	_btns.push_back(_btn_Quit);

	// Set buttons position
	for (int i = 0; i < _btns.size(); i++)
	{
		_btns[i]->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (70.0f * i) + 200.0f });
	}

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

	////////////////
	/*Event event;
	while (Engine::GetWindow().pollEvent(event))
	{
		if (event.type == Event::MouseButtonReleased)
		{
			Engine::ChangeScene(&scene_options);
		}
	}*/
	////////////////

	Scene::Update(dt);
}
