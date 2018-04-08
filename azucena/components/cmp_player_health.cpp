#include "cmp_player_health.h"
#include "system_resources.h"
#include "system_renderer.h"
#include "cmp_interactable.h"
#include "engine.h"

using namespace std;
using namespace sf;

PlayerHealthComponent::PlayerHealthComponent(Entity* p, int maxHealth, int maxPotions)
	: Component(p), _maxHealth(maxHealth), _health(maxHealth), _maxPotions(maxPotions), _potions(0)
{
}

void PlayerHealthComponent::update(double dt)
{
	if (_immunity >= 0.0f) _immunity -= dt;

  // Pick up potion
  auto potions = Engine::GetActiveScene()->ents.find("potion");
  for (auto potion : potions)
  {
    auto i = potion->get_components<InteractableComponent>()[0];
    if (i->interacted())
    {
      potion->setForDelete();
      addPotion();
    }
  }
}

void PlayerHealthComponent::render()
{
}

void PlayerHealthComponent::decreaseHealth(int h)
{
	if (_immunity < 0.0f)
	{
		int newHealth = _health - h;
		if (newHealth >= 0) _health = newHealth;
		_immunity = 0.8f;
		printf("Player hurt.\n");
	}

}

void PlayerHealthComponent::decreaseHealth()
{
	decreaseHealth(1);
}

void PlayerHealthComponent::increaseHealth(int h)
{
	int newHealth = _health + h;
	if (newHealth < _maxHealth) _health = newHealth;
}

void PlayerHealthComponent::increaseHealth()
{
	increaseHealth(1);
}

int PlayerHealthComponent::getHealth() { return _health; }

int PlayerHealthComponent::getMaxHealth() { return _maxHealth; }

void PlayerHealthComponent::usePotion()
{
	if (_potions > 0)
	{
		_health = _maxHealth;
		_potions--;
	}
}

void PlayerHealthComponent::addPotion(int i)
{
  if (_potions + 1 <= _maxPotions)
    _potions++;
  else
    usePotion();
}

void PlayerHealthComponent::addPotion()
{
  addPotion(1);
}

int PlayerHealthComponent::getPotions()
{
  return _potions;
}

int PlayerHealthComponent::getMaxPotions()
{
  return _maxPotions;
}