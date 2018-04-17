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

	// Messages
	std::vector<std::string> _bottomMessages = {
		"Use [W] [A] [D] [S] to move.\nUse [Space] to dash.\nUse [/] to spit.", // 0
		"Hold [Q] to pick up.", // 1
		"Use the heling herb with [E].", // 2
		"Your health increased!", // 3
		"You can carry one more healing herb!", // 4
		"Now you can spit quicker!" // 5
	};
	std::shared_ptr<Entity> _bottomMessage;
	float _bottomMessageTimer;

public:
	GameUIComponent() = delete;
	explicit GameUIComponent(Entity* p, std::shared_ptr<Entity> player);
	void update(double dt) override;
	void render() override;
	void showExitMessage();
	void showBottomMessage(int);
};