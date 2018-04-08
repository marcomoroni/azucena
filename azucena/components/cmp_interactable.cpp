#include "cmp_interactable.h"
#include "engine.h"
#include "cmp_sprite.h"
#include "system_resources.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

void InteractableComponent::update(double dt)
{
  bool playerIsClose = false;

  if (length(_parent->getPosition() - _player->getPosition()) < _playerInteractionDistance)
  {
    playerIsClose = true;
  }

  _interacted = false;

  if (playerIsClose)
  {
    _interactionTimerSprite->setVisible(true);
    _interactionTimerSprite->setPosition(_player->getPosition() + Vector2f(0.0f, 64.0f));
    if (Keyboard::isKeyPressed(Keyboard::E))
    {
      _interactionTimer += dt;
    }
    else
    {
      _interactionTimer = 0.0f;
    }

    // Change sprite according to timer
    // Note: there are 4 sprites
    auto s = _interactionTimerSprite->get_components<SpriteComponent>()[0];
    if (_interactionTimer == 0.0f)
    {
      // Empty
      s->getSprite().setTextureRect(sf::IntRect(32 * 7, 32 * 3, 32, 32));
    }
    else if (_interactionTimer <= _interactionTimeNeeded / 4)
    {
      // 1/4 circle
      s->getSprite().setTextureRect(sf::IntRect(32 * 8, 32 * 3, 32, 32));
    }
    else if (_interactionTimer <= _interactionTimeNeeded / 2)
    {
      // half circle
      s->getSprite().setTextureRect(sf::IntRect(32 * 9, 32 * 3, 32, 32));
    }
    else if (_interactionTimer <= _interactionTimeNeeded / 4 * 3)
    {
      // 3/4 circle
      s->getSprite().setTextureRect(sf::IntRect(32 * 7, 32 * 4, 32, 32));
    }
    else if (_interactionTimer <= _interactionTimeNeeded - 0.2f)
    {
      // Full circle
      s->getSprite().setTextureRect(sf::IntRect(32 * 8, 32 * 4, 32, 32));
    }

    if (_interactionTimer >= _interactionTimeNeeded)
    {
      _interacted = true;
    }
  }
  else
  {
    _interactionTimerSprite->setVisible(false);
    _interactionTimer = 0.0f;
  }
}

InteractableComponent::InteractableComponent(Entity* p, float playerInteractionDistance, float interactionTime)
  : Component(p), _playerInteractionDistance(playerInteractionDistance), _interactionTimeNeeded(interactionTime), _interactionTimer(0.0f)
{
  _interacted = false;

  _player = &(*(Engine::GetActiveScene()->ents.find("player")[0]));

  _interactionTimerSprite = &(*(Engine::GetActiveScene()->makeEntity()));

  auto s = _interactionTimerSprite->addComponent<SpriteComponent>();
  auto tex = Resources::get<Texture>("tex.png");
  s->setTexture(tex);
  s->getSprite().setTextureRect(sf::IntRect(32 * 7, 32 * 3, 32, 32));
  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
}

bool InteractableComponent::interacted()
{
  return _interacted;
}