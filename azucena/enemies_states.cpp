#include "enemies_states.h"
#include "prefabs.h"
#include <random>
#include <chrono>
#include "components/cmp_sprite.h"
#include "components/cmp_physics.h"
#include "components/cmp_hurt.h"

using namespace sf;
using namespace std::chrono;
using namespace std;

// ENEMY A ////////////////////////////////////////////////////////////////////

void EnemyA_IdleState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

	// Chase player when is sight
	if (length(owner->getPosition() - _player->getPosition()) < 200.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}

void EnemyA_ChaseState::execute(Entity *owner, double dt) noexcept
{
	// Chase player
	Vector2f direction = normalize(_player->getPosition() - owner->getPosition());
	direction.y *= -1; // why?
	float speed = 80.0f;
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(direction * speed));

	// If the player is too far away retrun to initial position
	if (length(owner->getPosition() - _player->getPosition()) > 600.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("return");
	}

	// If enemy is close to player, prepare attack
	if (length(owner->getPosition() - _player->getPosition()) < 200.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("prepare_attack");
	}
}

void EnemyA_ReturnState::execute(Entity *owner, double dt) noexcept
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

  // Chase player when is sight
  if (length(owner->getPosition() - _player->getPosition()) < 200.0f)
  {
    auto sm = owner->get_components<StateMachineComponent>()[0];
    sm->changeState("chase");
  }
}

void EnemyA_PrepareAttackState::enterState(Entity *owner) noexcept
{
	_timer = 1.0f;
}

void EnemyA_PrepareAttackState::execute(Entity *owner, double dt) noexcept
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

void EnemyA_AttackState::enterState(Entity *owner) noexcept
{
	_timer = 1.6f;
	_direction = normalize(_player->getPosition() - owner->getPosition());
	_direction.y *= -1; // why?
	// Can hurt player
	owner->get_components<HurtComponent>()[0]->setActive(true);
}

void EnemyA_AttackState::execute(Entity *owner, double dt) noexcept
{
	_timer -= dt;

	// Quick attack without changing direction,
	// after a while the enemy has to rest before going back to chase

	float speed = 500.0f;

	if (_timer < 0.5f)
	{
		speed = 30.0f;
	}

	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(_direction * speed));

	if (_timer < 0.0f)
	{
		owner->get_components<HurtComponent>()[0]->setActive(false);
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}

// ENEMY B ////////////////////////////////////////////////////////////////////

void EnemyB_IdleState::execute(Entity *owner, double dt) noexcept
{
  // Don't move
  owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

  // Move when player is sight
  if (length(owner->getPosition() - _player->getPosition()) < 200.0f)
  {
    auto sm = owner->get_components<StateMachineComponent>()[0];
    sm->changeState("move");
  }
}

void EnemyB_MoveState::enterState(Entity *owner) noexcept
{
  _timer = 0.0f;
  //_movementStep = 0;
  for (int i = 0; i < 3; i++)
  {
    random_device dev;
    default_random_engine engine(dev());
    uniform_int_distribution<int> dir(0, 3);
    _directionsStack.push_back(_directions[dir(engine)]);
  }
}

// Move three time in random orthogonal direction
void EnemyB_MoveState::execute(Entity *owner, double dt) noexcept
{
  float speed = 100.0f;

  if (_timer <= 0.0f && _directionsStack.size() <= 0)
  {
    auto sm = owner->get_components<StateMachineComponent>()[0];
    sm->changeState("shoot");
  }

  if (_timer <= 0.0f && _directionsStack.size() > 0)
  {
    _timer = 0.8f;
    _direction = _directionsStack[_directionsStack.size() - 1];
    _directionsStack.pop_back();
  }
  else if (_timer < 0.2f)
  {
    speed = 0.0f;
  }

  owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(_direction * speed));
  
  _timer -= dt;
}

void EnemyB_ShootState::execute(Entity *owner, double dt) noexcept
{
  // Shoot 4 projectiles
  create_enemy_B_bullet(owner, Vector2f{ 1.0f, 0.0f });
  create_enemy_B_bullet(owner, Vector2f{ -1.0f, 0.0f });
  create_enemy_B_bullet(owner, Vector2f{ 0.0f, 1.0f });
  create_enemy_B_bullet(owner, Vector2f{ 0.0f, -1.0f });

  auto sm = owner->get_components<StateMachineComponent>()[0];
  sm->changeState("move");
}

// ENEMY C ////////////////////////////////////////////////////////////////////

void EnemyC_IdleState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

	// Move when player is sight
	if (length(owner->getPosition() - _player->getPosition()) < 400.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("flee");
	}
}

void EnemyC_FleeState::enterState(Entity *owner) noexcept
{
	_timer = 3.0f;
}

void EnemyC_FleeState::execute(Entity *owner, double dt) noexcept
{
	// Flee from player
	Vector2f direction = normalize(_player->getPosition() - owner->getPosition());
	direction.y *= -1; // why?

	// Move by 90 degrees
	Transform rotation;
	rotation.rotate(90, 0, 0);
	direction = rotation.transformPoint(direction);

	float speed = 40.0f;
	if (_timer < 1.0f) speed = 0.0f;
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(direction * speed));

	_timer -= dt;

	// If enemy is close to player, prepare attack
	if (_timer <= 0.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("shoot");
	}
}

void EnemyC_ShootState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<PhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

	// Shoot 3 projectiles
	Vector2f direction = normalize(_player->getPosition() - owner->getPosition());
	Transform rotation1;
	rotation1.rotate(_angle, 0, 0);
	Transform rotation2;
	rotation2.rotate(-_angle, 0, 0);
	create_enemy_C_bullet(owner, direction);
	create_enemy_C_bullet(owner, rotation1.transformPoint(direction));
	create_enemy_C_bullet(owner, rotation2.transformPoint(direction));

	auto sm = owner->get_components<StateMachineComponent>()[0];
	sm->changeState("flee");
}