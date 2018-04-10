#pragma once

#include <ecm.h>
#include "SFML/Graphics.hpp"
#include "cmp_player_health.h"

class GameUIComponent : public Component
{
private:
	std::shared_ptr<Entity> _player;

	std::shared_ptr<sf::Texture> _tex;

	float _margin;

	// Player health
	int _player_health_sprite_size;
	std::vector<sf::Sprite> _player_health_hearts;

	// Potions
	int _player_potion_sprite_size;
	std::vector<sf::Sprite> _player_potions;

	// Exit message
	std::shared_ptr<Entity> _exitMessage;
	float _exitMessageTimer;

public:
	GameUIComponent() = delete;
	explicit GameUIComponent(Entity* p, std::shared_ptr<Entity> player);
	void update(double dt) override;
	void render() override;
	void showExitMessage();
};