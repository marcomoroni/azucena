#include "enemies_states.h"
#include "components/cmp_sprite.h"
#include "components/cmp_physics.h"

using namespace sf;

void IdleState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

	// Chase player when is sight
	if (length(owner->getPosition() - _player->getPosition()) < 400.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}

void ChaseState::execute(Entity *owner, double dt) noexcept
{
	// Chase player
	Vector2f direction = normalize(_player->getPosition() - owner->getPosition());
	direction.y *= -1; // why?
	float speed = 100.0f;
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(direction * speed));

	// If the player is too far away retrun to initial position
	if (length(owner->getPosition() - _player->getPosition()) > 600.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("return");
	}

	// If enemy is close to player, prepare attack
	if (length(owner->getPosition() - _player->getPosition()) < 160.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("prepare_attack");
	}
}

void ReturnState::execute(Entity *owner, double dt) noexcept
{
	// Go back to original position
	Vector2f direction = normalize(_pos - owner->getPosition());
	direction.y *= -1; // why?
	float speed = 80.0f;
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(direction * speed));

	// When arrive to inital position, change to idle state
	if (length(owner->getPosition() - _pos) < 5.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("idle");
	}
}

void PrepareAttackState::enterState(Entity *owner) noexcept
{
	_timer = 0.6f;
}

void PrepareAttackState::execute(Entity *owner, double dt) noexcept
{
	// Simulate a funnisng start
	Vector2f direction = -normalize(_player->getPosition() - owner->getPosition());
	direction.y *= -1; // why?
	float speed = 60.0f;
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(direction * speed));

	_timer -= dt;

	if (_timer < 0.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("attack");
	}
}

void AttackState::enterState(Entity *owner) noexcept
{
	_timer = 0.9f;
	_direction = normalize(_player->getPosition() - owner->getPosition());
	_direction.y *= -1; // why?
}

void AttackState::execute(Entity *owner, double dt) noexcept
{
	_timer -= dt;

	// Quick attack without changing direction,
	// after a while the enemy has to rest before going back to chase

	float speed = 600.0f;

	if (_timer < 0.5f)
	{
		speed = 30.0f;
	}

	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(_direction * speed));

	// If hits player, decrease health
	// ...

	if (_timer < 0.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}