#include "main_collectible_states.h"
#include "components/cmp_physics.h"
#include "system_resources.h"

using namespace sf;
using namespace std;

void MainCollectible_LostState::execute(Entity *owner, double dt) noexcept
{
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

	if (length(owner->getPosition() - _player->getPosition()) < 60.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("happy");
	}
}

MainCollectible_HappyState::MainCollectible_HappyState()
{
	// Sounds
	_buffer_jump = *(Resources::get<SoundBuffer>("baby_llama_happy.wav"));
	_sound_jump.setBuffer(_buffer_jump);
	_sound_jump.setVolume(70);
}

void MainCollectible_HappyState::enterState(Entity *owner) noexcept
{
	_jumpLoop = 0.0f;
}

void MainCollectible_HappyState::execute(Entity *owner, double dt) noexcept
{
	float speed = 80.0f;
	Vector2f direction = { 0.0f, 0.0f };

	_jumpLoop += dt;

	// Total jump time
	if (_jumpLoop > 0.8f) _jumpLoop = 0.0f;

	// 0.0 - 0.2 -> up
	// 0.2 - 0.4 -> down
	// 0.4 - 0.8 -> rest
	if (_jumpLoop == 0.0f) _sound_jump.play();
	if (_jumpLoop >= 0.0f && _jumpLoop < 0.2f)
	{
		direction = { 0.0f, 1.0f };
	}
	if (_jumpLoop >= 0.2f && _jumpLoop < 0.4f)
	{
		direction = { 0.0f, -1.0f };
	}
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(direction * speed));
}

void MainCollectible_IdleState::execute(Entity *owner, double dt) noexcept
{
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));
}