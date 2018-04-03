#pragma once

#include "components/cmp_state_machine.h"

class Door_CloseState : public State
{
private:
  std::shared_ptr<Entity> _player;
  std::shared_ptr<Entity> _key;

public:
  Door_CloseState(std::shared_ptr<Entity> player, std::shared_ptr<Entity> key)
    : _player(player), _key(key) {}
  void enterState(Entity*) noexcept override {}
  void execute(Entity*, double) noexcept override;
};

class Door_OpenState : public State
{
public:
  Door_OpenState() {}
  void enterState(Entity*) noexcept override;
  void execute(Entity*, double) noexcept override {}
};