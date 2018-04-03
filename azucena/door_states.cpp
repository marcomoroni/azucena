#include "door_states.h"
#include "components/cmp_physics.h"
#include "components/cmp_sprite.h"
#include "key_states.h"

using namespace sf;
using namespace std;

void Door_CloseState::execute(Entity *owner, double dt) noexcept
{
  auto ksm = _key->get_components<StateMachineComponent>()[0];

  if (
    // Player is near door and
    length(owner->getPosition() - _player->getPosition()) < 120.0f &&
    // player has key
    ksm->currentState() == "taken")
  {
    // Set key as used
    ksm->changeState("used");

    auto sm = owner->get_components<StateMachineComponent>()[0];
    sm->changeState("open");
  }
}

void Door_OpenState::enterState(Entity *owner) noexcept
{
  auto pc = owner->get_components<PhysicsComponent>()[0];
  pc->getBody()->DestroyFixture(pc->getFixture());

  // Make it invisible
  auto sc = owner->get_components<SpriteComponent>()[0];
  sc->getSprite().setTextureRect(IntRect(32 * 2, 32, 32, 32));
}