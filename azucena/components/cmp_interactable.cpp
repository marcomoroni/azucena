#include "cmp_interactable.h"
#include "engine.h"
#include "cmp_sprite.h"
#include "system_resources.h"
#include <SFML/Window/Keyboard.hpp>
#include "../constrols.h"

using namespace std;
using namespace sf;

void InteractableComponent::update(double dt)
{
  if (_active)
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
      if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Interact")))
      {
        _interactionTimer += dt;
				_sound_interactionTimer.play();
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

			// Interacted
      if (_interactionTimer >= _interactionTimeNeeded)
      {
				_sound_interacted.play();
        _interacted = true;
        _interactionTimerSprite->setVisible(false);
      }
    }
    else
    {
      _interactionTimerSprite->setVisible(false);
      _interactionTimer = 0.0f;
    }
  }
}

InteractableComponent::InteractableComponent(Entity* p, float playerInteractionDistance, float interactionTime)
  : Component(p), _playerInteractionDistance(playerInteractionDistance), _interactionTimeNeeded(interactionTime), _interactionTimer(0.0f)
{
  _interacted = false;
  _active = true;

  _player = &(*(Engine::GetActiveScene()->ents.find("player")[0]));

  _interactionTimerSprite = &(*(Engine::GetActiveScene()->makeEntity()));

  auto s = _interactionTimerSprite->addComponent<SpriteComponent>();
  auto tex = Resources::get<Texture>("tex.png");
  s->setTexture(tex);
  s->getSprite().setTextureRect(sf::IntRect(32 * 7, 32 * 3, 32, 32));
  s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	// Sounds
	_buffer_interactionTimer = *(Resources::get<SoundBuffer>("interaction_timer.wav"));
	_sound_interactionTimer.setBuffer(_buffer_interactionTimer);
	_buffer_interacted = *(Resources::get<SoundBuffer>("interacted.wav"));
	_sound_interacted.setBuffer(_buffer_interacted);
}

bool InteractableComponent::interacted()
{
  return _interacted;
}

void InteractableComponent::setActive(bool a)
{
  _active = a;
  _interactionTimerSprite->setAlive(a);
  _interactionTimerSprite->setVisible(a);
}