#pragma once

#include "components/cmp_state_machine.h"

class EnemyA_IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	EnemyA_IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class EnemyA_ChaseState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	EnemyA_ChaseState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class EnemyA_ReturnState : public State
{
private:
	sf::Vector2f _pos;

public:
	EnemyA_ReturnState(sf::Vector2f pos)
		: _pos(pos) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class EnemyA_PrepareAttackState : public State
{
private:
	std::shared_ptr<Entity> _player;
	float _timer;

public:
	EnemyA_PrepareAttackState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void execute(Entity*, double) noexcept override;
	void enterState(Entity*) noexcept override;
};

class EnemyA_AttackState : public State
{
private:
	std::shared_ptr<Entity> _player;
	sf::Vector2f _direction;
	float _timer;

public:
	EnemyA_AttackState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void execute(Entity*, double) noexcept override;
	void enterState(Entity*) noexcept override;
};