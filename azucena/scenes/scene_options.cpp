#include "scene_options.h"
#include "../game.h"
#include "SFML/Window/Keyboard.hpp"
#include "../prefabs.h"
#include "../constrols.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> btn_ControlsUp;
shared_ptr<Entity> btn_ControlsDown;
shared_ptr<Entity> btn_ControlsLeft;
shared_ptr<Entity> btn_ControlsRight;
shared_ptr<Entity> btn_ControlsDash;
shared_ptr<Entity> btn_ControlsShoot;
shared_ptr<Entity> btn_Back;
// All buttons
vector<shared_ptr<Entity>> btns;
// Map button to control
map<shared_ptr<Entity>, string> controlsBtns;
// The control being changed
shared_ptr<Entity> changingControl = nullptr;

void OptionsScene::Load()
{
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("Options");
		txt->setPosition({ (float)Engine::GetWindow().getSize().x / 2, 100.0f });
	}

	btns.clear();

  btn_ControlsUp.reset();
	btn_ControlsUp = create_button("Up");
	btns.push_back(btn_ControlsUp);
	controlsBtns[btn_ControlsUp] = "Up";

  btn_ControlsDown.reset();
	btn_ControlsDown = create_button("Down");
	btns.push_back(btn_ControlsDown);
	controlsBtns[btn_ControlsDown] = "Down";

  btn_ControlsLeft.reset();
	btn_ControlsLeft = create_button("Left");
	btns.push_back(btn_ControlsLeft);
	controlsBtns[btn_ControlsLeft] = "Left";

  btn_ControlsRight.reset();
	btn_ControlsRight = create_button("Right");
	btns.push_back(btn_ControlsRight);
	controlsBtns[btn_ControlsRight] = "Right";

  btn_ControlsDash.reset();
	btn_ControlsDash = create_button("Dash");
	btns.push_back(btn_ControlsDash);
	controlsBtns[btn_ControlsDash] = "Sprint";

  btn_ControlsDash.reset();
	btn_ControlsDash = create_button("Shoot");
	btns.push_back(btn_ControlsDash);
	controlsBtns[btn_ControlsDash] = "Shoot";

  btn_Back.reset();
	btn_Back = create_button("Back");
	btns.push_back(btn_Back);

	// Set buttons position
	for (int i = 0; i < btns.size(); i++)
	{
		btns[i]->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (40.0f * i) + 200.0f });
	}

	// Show corresponding keys
	// ...

	// Set view
	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void OptionsScene::Update(const double& dt)
{
	if (btn_Back->get_components<ButtonComponent>()[0]->isSelected())
	{
		Engine::ChangeScene(&menu);
	}

	// Select key to be changed
	if (changingControl == nullptr)
	{
		for (auto b : controlsBtns)
		{
			if (b.first->get_components<ButtonComponent>()[0]->isSelected())
			{
				changingControl = b.first;
				// Change text colour
				b.first->get_components<TextComponent>()[0]->getText()->setColor(Color::Red);
			}
		}
	}

	// Change key
	if (changingControl != nullptr)
	{
		// Since without events we cannot get the key pressed,
		// we loop though all the keys and if one is pressed, we set it to the
		// control that is being changed
		for (auto k = Keyboard::Unknown; k != Keyboard::Pause; k = static_cast<Keyboard::Key>(k + 1))
		{
			if (Keyboard::isKeyPressed(k))
			{
				Controls::SetKeyboardKey(controlsBtns[changingControl], k);
				// Change back text colour
				changingControl->get_components<TextComponent>()[0]->getText()->setColor(Color::White);
				changingControl = nullptr;
			}
		}
	}

	Scene::Update(dt);
}