#pragma once

#include "components/cmp_state_machine.h"
#include <SFML/Audio.hpp>

class Door_CloseState : public State
{
private:
	std::shared_ptr<Entity> _player;
	std::shared_ptr<Entity> _key;

public:
	Door_CloseState(std::shared_ptr<Entity> player)
		: _player(player) {}
	void enterState(Entity*) noexcept override;
	void execute(Entity*, double) noexcept override;
};

class Door_OpenState : public State
{
private:
	// Sounds
	sf::SoundBuffer _buffer_openDoor;
	sf::Sound _sound_openDoor;

public:
	Door_OpenState();
	void enterState(Entity*) noexcept override;
	void execute(Entity*, double) noexcept override {}
};