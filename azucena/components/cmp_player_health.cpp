#include "cmp_player_health.h"
#include "system_resources.h"
#include "system_renderer.h"
#include "cmp_interactable.h"
#include "engine.h"
#include "../data.h"

using namespace std;
using namespace sf;

PlayerHealthComponent::PlayerHealthComponent(Entity* p)
	: Component(p)
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
		int newHealth = Data::health - h;
		if (newHealth >= 0) Data::health = newHealth;
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
	int newHealth = Data::health + h;
	if (newHealth < Data::max_health) Data::health = newHealth;
}

void PlayerHealthComponent::increaseHealth()
{
	increaseHealth(1);
}

int PlayerHealthComponent::getHealth() { return Data::health; }

int PlayerHealthComponent::getMaxHealth() { return Data::max_health; }

void PlayerHealthComponent::usePotion()
{
	if (Data::potions > 0)
	{
		Data::health = Data::max_health;
    Data::potions--;
	}
}

void PlayerHealthComponent::addPotion(int i)
{
  if (Data::potions + 1 <= Data::max_potions)
    Data::potions++;
  else
    usePotion();
}

void PlayerHealthComponent::addPotion()
{
  addPotion(1);
}

int PlayerHealthComponent::getPotions()
{
  return Data::potions;
}

int PlayerHealthComponent::getMaxPotions()
{
  return Data::max_potions;
}