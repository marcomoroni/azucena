#pragma once

#include <ecm.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

class PlayerHealthComponent : public Component
{
private:
	float _immunity = -1.0f;
	bool _usePotionButtonStillPressed;

	// Sounds
	sf::SoundBuffer _buffer_usePotion;
	sf::Sound _sound_usePotion;
	sf::SoundBuffer _buffer_getsHit;
	sf::Sound _sound_getsHit;

public:
	void update(double) override;
	void render() override;
	explicit PlayerHealthComponent(Entity* p);
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