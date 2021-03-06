#include "key_states.h"
#include "engine.h"
#include "components/cmp_interactable.h"

using namespace sf;
using namespace std;

void Key_NotTakenState::execute(Entity *owner, double dt) noexcept
{
	auto i = owner->get_components<InteractableComponent>()[0];
	if (i->interacted())
	{
		i->setActive(false);
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("taken");
	}
}

void Key_TakenState::enterState(Entity *owner) noexcept
{
	_door = Engine::GetActiveScene()->ents.find("door")[0];
}

void Key_TakenState::execute(Entity *owner, double dt) noexcept
{
	Vector2f target;
	// Target is close to the player or, if player is close to
	// the door the target is the door
	if (length(_player->getPosition() - _door->getPosition()) > 130.0f)
	{
		target = _player->getPosition() + Vector2f(-40.0f, -40.0f);
	}
	else
	{
		target = _door->getPosition();
	}
	Vector2f direction = normalize(target - owner->getPosition());
	float speed = 100.0f;
	// Faster if far away or 0 if very close to target
	if (length(target - owner->getPosition()) > 60.0f)
	{
		speed = 300.0f;
	}
	else if (length(target - owner->getPosition()) < 0.3f)
	{
		speed = 0.0f;
	}

	owner->setPosition(owner->getPosition() + (direction * speed * (float)dt));
}

void Key_UsedState::enterState(Entity *owner) noexcept
{
	owner->setForDelete();
}