#pragma once

#include <ecm.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class PlayerHealthComponent : public Component
{
private:
	int _maxHealth;
	int _health;
	int _maxPotions = 4;
	int _potions = 0;
	float _immunity = -1.0f;

public:
	void update(double) override;
	void render() override;
	explicit PlayerHealthComponent(Entity* p, int maxHealth, int maxPotions);
	PlayerHealthComponent() = delete;
	void decreaseHealth();
	void decreaseHealth(int);
	void increaseHealth();
	void increaseHealth(int);
	int getHealth();
	int getMaxHealth();
	void usePotion();
	void addPotion();
	void addPotion(int);
  int getPotions();
  int getMaxPotions();
};