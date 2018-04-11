#pragma once

#include "components/cmp_state_machine.h"

class FakeWall_HiddenState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	FakeWall_HiddenState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class FakeWall_RevealedState : public State
{
public:
	FakeWall_RevealedState() {}
	void enterState(Entity*) noexcept override;
	void execute(Entity*, double) noexcept override {};
};