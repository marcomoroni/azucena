#pragma once

#include "components/cmp_state_machine.h"

class IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class ChaseState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	ChaseState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class ReturnState : public State
{
private:
	sf::Vector2f _pos;

public:
	ReturnState(sf::Vector2f pos)
		: _pos(pos) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class PrepareAttackState : public State
{
private:
	std::shared_ptr<Entity> _player;
	float _timer;

public:
	PrepareAttackState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void execute(Entity*, double) noexcept override;
	void enterState(Entity*) noexcept override;
};

class AttackState : public State
{
private:
	std::shared_ptr<Entity> _player;
	sf::Vector2f _direction;
	float _timer;

public:
	AttackState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void execute(Entity*, double) noexcept override;
	void enterState(Entity*) noexcept override;
};