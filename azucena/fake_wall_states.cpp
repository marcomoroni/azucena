#include "fake_wall_states.h"

using namespace sf;
using namespace std;

void FakeWall_HiddenState::execute(Entity *owner, double dt) noexcept
{
	if (length(_player->getPosition() - owner->getPosition()) < 32.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("revealed");
	}
}

void FakeWall_RevealedState::enterState(Entity *owner) noexcept
{
	owner->setVisible(false);
}