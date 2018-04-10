#pragma once

#include "components/cmp_state_machine.h"
#include <SFML/Audio.hpp>

class MainCollectible_LostState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	MainCollectible_LostState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {}
	void execute(Entity*, double) noexcept override;
};

class MainCollectible_HappyState : public State
{
private:
	float _jumpLoop;

	// Sounds
	sf::SoundBuffer _buffer_jump;
	sf::Sound _sound_jump;

public:
	MainCollectible_HappyState();
	void enterState(Entity*) noexcept override;
	void execute(Entity*, double) noexcept override;
};

// For when it is on center scene
class MainCollectible_IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	MainCollectible_IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override {}
	void execute(Entity*, double) noexcept override;
};