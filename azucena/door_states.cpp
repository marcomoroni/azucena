#include "door_states.h"
#include "components/cmp_physics.h"
#include "components/cmp_sprite.h"
#include "key_states.h"
#include "engine.h"
#include "game.h"

using namespace sf;
using namespace std;

void Door_CloseState::enterState(Entity *owner) noexcept
{
  //_key = Engine::GetActiveScene()->ents.find("key")[0];
}

void Door_CloseState::execute(Entity *owner, double dt) noexcept
{
  _key = Engine::GetActiveScene()->ents.find("key")[0];
  auto ksm = _key->get_components<StateMachineComponent>()[0];

  if (
    // key is close to door
    length(_key->getPosition() - owner->getPosition()) < 1.0f
    )
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