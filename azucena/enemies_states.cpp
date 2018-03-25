#include "enemies_states.h"
#include "components/cmp_sprite.h"
#include "components/cmp_enemy_health.h"

using namespace sf;

void NormalState::execute(Entity *owner, double dt) noexcept
{
	// TEST
	owner->setRotation(0.0f);

	if (length(owner->getPosition() - _player->getPosition()) < 100.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("near");
	}
}

void NearState::execute(Entity *owner, double dt) noexcept
{
	// TEST
	owner->setRotation(90.0f);

	if (length(owner->getPosition() - _player->getPosition()) > 100.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("normal");
	}
}