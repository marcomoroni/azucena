#include "cmp_interactable.h"
#include "engine.h"
#include "cmp_sprite.h"
#include "system_resources.h"

using namespace std;
using namespace sf;

void InteractableComponent::update(double dt)
{
  bool playerIsClose = false;

  if (length(_parent->getPosition() - _player->getPosition()) < _playerInteractionDistance)
  {
    playerIsClose = true;
  }

  if (playerIsClose)
  {
    _pickUpTimerSprite->setVisible(true);
    _pickUpTimerSprite->setPosition(_player->getPosition() + Vector2f(0.0f, -32.0f));
  }
  else
  {
    _pickUpTimerSprite->setVisible(false);
  }
}

InteractableComponent::InteractableComponent(Entity* p, float playerInteractionDistance)
  : Component(p), _playerInteractionDistance(playerInteractionDistance)
{
  _player = &(*(Engine::GetActiveScene()->ents.find("player")[0]));

  _pickUpTimerSprite = &(*(Engine::GetActiveScene()->makeEntity()));

  auto s = _pickUpTimerSprite->addComponent<SpriteComponent>();
  auto tex = Resources::get<Texture>("tex.png");
  s->setTexture(tex);
  s->getSprite().setTextureRect(sf::IntRect(32 * 7, 32 * 3, 32, 32));
  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
}
