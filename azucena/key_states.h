#pragma once

#include "components/cmp_state_machine.h"

class Key_NotTakenState : public State
{
private:
  std::shared_ptr<Entity> _player;

public:
  Key_NotTakenState(std::shared_ptr<Entity> player)
    : _player(player) {}
  void enterState(Entity*) noexcept override {}
  void execute(Entity*, double) noexcept override;
};

class Key_TakenState : public State
{
private:
  std::shared_ptr<Entity> _player;

public:
  Key_TakenState(std::shared_ptr<Entity> player)
    : _player(player) {}
  Key_TakenState() {}
  void enterState(Entity*) noexcept override {}
  void execute(Entity*, double) noexcept override;
};

class Key_UsedState : public State
{
public:
  Key_UsedState() {}
  void enterState(Entity*) noexcept override;
  void execute(Entity*, double) noexcept override {};
};