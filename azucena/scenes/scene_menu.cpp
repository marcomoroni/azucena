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
		// Logo
		auto logo = makeEntity();
		auto s = logo->addComponent<SpriteComponent>();
		auto t = Resources::get<Texture>("logo.png");
		s->setTexture(t);
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
		logo->setPosition({ (float)Engine::GetWindow().getSize().x / 2 - s->getSprite().getGlobalBounds().width / 2 - 80.0f , (float)Engine::GetWindow().getSize().y / 2 });
	}

	_btns.clear();

	_btn_Continue.reset();
	_btn_Continue = create_button("Continue");
	_btns.push_back(_btn_Continue);

	_btn_Start.reset();
	_btn_Start = create_button("New game");
	_btns.push_back(_btn_Start);

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
		if (i == 0)
		{
			_btns[i]->setPosition({
				(float)Engine::GetWindow().getSize().x / 2 + (500.0f / 2) + 10.0f,
				(float)Engine::GetWindow().getSize().y / 2 - ((38.0f * (_btns.size() - 1)) / 2)
			});
		}
		else
		{
			_btns[i]->setPosition({ _btns[i - 1]->getPosition().x, _btns[i - 1]->getPosition().y + 38.0f });
		}
	}

	_clickCooldown = 0.2f;

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void MenuScene::Update(const double& dt) {

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

	if (_clickCooldown >= 0.0f) _clickCooldown -= dt;

	if (_clickCooldown < 0.0f)
	{
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
	}

	Scene::Update(dt);
}
