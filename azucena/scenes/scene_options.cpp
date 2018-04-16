#include "scene_options.h"
#include "../game.h"
#include "SFML/Window/Keyboard.hpp"
#include "../prefabs.h"
#include "../controls.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

void OptionsScene::Load()
{
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Options");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
		t->getText()->setColor(Color(255, 218, 194));
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
	_btn_ControlsShoot = create_button("Spit [RShift]");
	_btns.push_back(_btn_ControlsShoot);
	_controlsBtns[_btn_ControlsShoot] = "Shoot";

	_btn_ControlsInteract.reset();
	_btn_ControlsInteract = create_button("Interact [Q]");
	_btns.push_back(_btn_ControlsInteract);
	_controlsBtns[_btn_ControlsInteract] = "Interact";

	_btn_ControlsUsePotion.reset();
	_btn_ControlsUsePotion = create_button("Use potion [/]");
	_btns.push_back(_btn_ControlsUsePotion);
	_controlsBtns[_btn_ControlsUsePotion] = "Use potion";

	_btn_Back.reset();
	_btn_Back = create_button("Back");
	_btns.push_back(_btn_Back);

	// Set buttons position
	for (int i = 0; i < _btns.size(); i++)
	{
		_btns[i]->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (38.0f * i) + 200.0f });
	}

	_clickCooldown = 0.2f;

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void OptionsScene::Update(const double& dt)
{
	if (_clickCooldown >= 0.0f) _clickCooldown -= dt;

	if (_clickCooldown < 0.0f)
	{
		if (_btn_Back->get_components<ButtonComponent>()[0]->isSelected())
		{
			Engine::ChangeScene(&scene_menu);
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

	Scene::Update(dt);
}