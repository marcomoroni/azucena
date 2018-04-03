#include "key_states.h"

using namespace sf;
using namespace std;

void Key_NotTakenState::execute(Entity *owner, double dt) noexcept
{
  if (length(owner->getPosition() - _player->getPosition()) < 10.0f)
  {
    auto sm = owner->get_components<StateMachineComponent>()[0];
    sm->changeState("taken");
  }
}

void Key_TakenState::execute(Entity *owner, double dt) noexcept
{
  //float speed = 30.0f;
  Vector2f target = _player->getPosition() + Vector2f(-40.0f, -40.0f);
  Vector2f direction = normalize(target - owner->getPosition());
  float speed = 2.0f;
  if (length(target - owner->getPosition()) < 10.0f)
  {
    speed = 0.0f;
  }

  owner->setPosition(owner->getPosition() + (direction * speed));
}

void Key_UsedState::execute(Entity *owner, double dt) noexcept
{

}