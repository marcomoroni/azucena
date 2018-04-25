#include "scene_options.h"
#include "../game.h"
#include "SFML/Window/Keyboard.hpp"
#include "../prefabs.h"
#include "../controls.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

string OptionsScene::writeResolutionButtonText(int index)
{
	string s = "Resolution: " + to_string(Engine::resolutions[index].first) + " x " + to_string(Engine::resolutions[index].second);
	return s;
}

void OptionsScene::Load()
{
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Options");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
		t->getText()->setColor(Color(255, 218, 194));
		t->getText()->setOrigin(t->getText()->getLocalBounds().width / 2, t->getText()->getLocalBounds().height / 2 + 14.0f);
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2 - t->getText()->getGlobalBounds().width / 2 - 80.0f , (float)Engine::GetWindow().getSize().y / 2 });
	}

	_btns.clear();
	_changingControl.reset();

	_btn_ControlsUp.reset();
	_btn_ControlsUp = create_button("Up [W]");
	_btns.push_back(_btn_ControlsUp);
	_controlsBtns[_btn_ControlsUp] = "Up";

	_btn_ControlsDown.reset();
	_btn_ControlsDown = create_button("Down [S]");
	_btns.push_back(_btn_ControlsDown);
	_controlsBtns[_btn_ControlsDown] = "Down";

	_btn_ControlsLeft.reset();
	_btn_ControlsLeft = create_button("Left [A]");
	_btns.push_back(_btn_ControlsLeft);
	_controlsBtns[_btn_ControlsLeft] = "Left";

	_btn_ControlsRight.reset();
	_btn_ControlsRight = create_button("Right [D]");
	_btns.push_back(_btn_ControlsRight);
	_controlsBtns[_btn_ControlsRight] = "Right";

	_btn_ControlsDash.reset();
	_btn_ControlsDash = create_button("Dash [Space]");
	_btns.push_back(_btn_ControlsDash);
	_controlsBtns[_btn_ControlsDash] = "Sprint";

	_btn_ControlsShoot.reset();
	_btn_ControlsShoot = create_button("Spit [/]");
	_btns.push_back(_btn_ControlsShoot);
	_controlsBtns[_btn_ControlsShoot] = "Shoot";

	_btn_ControlsInteract.reset();
	_btn_ControlsInteract = create_button("Interact [Q]");
	_btns.push_back(_btn_ControlsInteract);
	_controlsBtns[_btn_ControlsInteract] = "Interact";

	_btn_ControlsUsePotion.reset();
	_btn_ControlsUsePotion = create_button("Use potion [E]");
	_btns.push_back(_btn_ControlsUsePotion);
	_controlsBtns[_btn_ControlsUsePotion] = "Use potion";

	_btn_Resolution.reset();
	_tempResolutionIndex = Engine::ResolutionIndex();
	_btn_Resolution = create_button(writeResolutionButtonText(_tempResolutionIndex));
	_btns.push_back(_btn_Resolution);

	_btn_Back.reset();
	_btn_Back = create_button("Back");
	_btns.push_back(_btn_Back);

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

void OptionsScene::Update(const double& dt)
{
	bool flag_back = false;

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	Engine::GetWindow().setView(view);

	if (_clickCooldown >= 0.0f) _clickCooldown -= dt;

	if (_clickCooldown < 0.0f)
	{
		// Back to menu
		if (_btn_Back->get_components<ButtonComponent>()[0]->isSelected())
		{
			flag_back = true;
		}

		// Select key to be changed
		if (_changingControl == nullptr)
		{
			for (auto b : _controlsBtns)
			{
				if (b.first->get_components<ButtonComponent>()[0]->isSelected())
				{
					_changingControl = b.first;
					// Change text colour
					b.first->get_components<TextComponent>()[0]->getText()->setColor(Color(254, 203, 82));
				}
			}
		}

		// Select resolution
		if (_btn_Resolution->get_components<ButtonComponent>()[0]->isSelected())
		{
			printf("bip\n");
			_clickCooldown = 0.2f;

			// Loop through resolutions
			int nextIndex;
			if (_tempResolutionIndex + 1 >= Engine::resolutions.size()) nextIndex = 0;
			else nextIndex = _tempResolutionIndex + 1;

			_tempResolutionIndex = nextIndex;

			_btn_Resolution->get_components<TextComponent>()[0]->getText()->setString(writeResolutionButtonText(_tempResolutionIndex));
		}
	}

	// Change key
	if (_changingControl != nullptr)
	{
		// Since without events we cannot get the key pressed,
		// we loop though all the keys and if one is pressed, we set it to the
		// control that is being changed
		for (auto k = Keyboard::Unknown; k != Keyboard::Pause; k = static_cast<Keyboard::Key>(k + 1))
		{
			if (Keyboard::isKeyPressed(k))
			{
				Controls::SetKeyboardKey(_controlsBtns[_changingControl], k);
				// Change back text colour
				_changingControl->get_components<TextComponent>()[0]->getText()->setColor(Color(198, 152, 127));
				_changingControl = nullptr;
			}
		}
	}

	// Change scene
	if (flag_back)
	{
		// Chenge resolution if different
		if (_tempResolutionIndex != Engine::ResolutionIndex()) Engine::ChangeResolution(_tempResolutionIndex);

		Engine::ChangeScene(&scene_menu);
	}

	Scene::Update(dt);
}