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

public:
	void update(double) override;
	void render() override;
	explicit PlayerHealthComponent(Entity* p, int maxHealth);
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
};