#include "door_states.h"
#include "components/cmp_physics.h"
#include "key_states.h"
#include "engine.h"
#include "game.h"
#include "system_resources.h"

using namespace sf;
using namespace std;

void Door_CloseState::enterState(Entity *owner) noexcept
{
	//_key = Engine::GetActiveScene()->ents.find("key")[0];
}

void Door_CloseState::execute(Entity *owner, double dt) noexcept
{
	_key = Engine::GetActiveScene()->ents.find("key")[0];
	auto ksm = _key->get_components<StateMachineComponent>()[0];

	if (
		// key is close to door
		length(_key->getPosition() - owner->getPosition()) < 1.0f
		)
	{
		// Set key as used
		ksm->changeState("used");

		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("open");
	}
}

Door_OpenState::Door_OpenState()
{
	// Sounds
	_buffer_openDoor = *(Resources::get<SoundBuffer>("open_door.wav"));
	_sound_openDoor.setBuffer(_buffer_openDoor);
}

void Door_OpenState::enterState(Entity *owner) noexcept
{
	_sound_openDoor.play();

	auto pc = owner->get_components<PhysicsComponent>()[0];
	pc->getBody()->DestroyFixture(pc->getFixture());

	owner->setForDelete();
}