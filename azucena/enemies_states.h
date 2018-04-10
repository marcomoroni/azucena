#pragma once

#include "components/cmp_state_machine.h"

// ENEMY A ////////////////////////////////////////////////////////////////////

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
	std::shared_ptr<Entity> _player;
	sf::Vector2f _pos;

public:
	EnemyA_ReturnState(sf::Vector2f pos, std::shared_ptr<Entity> player)
		: _pos(pos), _player(player) {}
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

// ENEMY B ////////////////////////////////////////////////////////////////////

class EnemyB_IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	EnemyB_IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class EnemyB_MoveState : public State
{
private:
	std::shared_ptr<Entity> _player;
	float _timer;
	std::vector<sf::Vector2f> _directions = {
	  sf::Vector2f(1.0f, 0.0f),
	  sf::Vector2f(-1.0f, 0.0f),
	  sf::Vector2f(0.0f, 1.0f),
	  sf::Vector2f(0.0f, -1.0f),
	};
	sf::Vector2f _direction;
	std::vector<sf::Vector2f> _directionsStack = {};

public:
	EnemyB_MoveState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override;
	void execute(Entity*, double) noexcept override;
};

class EnemyB_ShootState : public State
{
public:
	EnemyB_ShootState() {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

// ENEMY C ////////////////////////////////////////////////////////////////////

class EnemyC_IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	EnemyC_IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class EnemyC_FleeState : public State
{
private:
	std::shared_ptr<Entity> _player;
	float _timer;

public:
	EnemyC_FleeState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override;
	void execute(Entity*, double) noexcept override;
};

class EnemyC_ShootState : public State
{
private:
	std::shared_ptr<Entity> _player;
	float _angle;

public:
	EnemyC_ShootState(std::shared_ptr<Entity> player)
		: _player(player), _angle(10.0f) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};