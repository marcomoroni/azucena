#pragma once

#include "ecm.h"
#include <SFML/Audio.hpp>

class PlayerControlsComponent : public Component {
protected:
  float _groundspeed;
	bool _isSprinting;
	// Timer until player can sprint again
	double _sprintCooldown;
	float _sprintSpeed;
	// Player cannot change direction when sprinting
	sf::Vector2f _sprintDirection;
	// Has to press Space again to sprint (cannot keep Space pressed)
	bool _isStillPressingSprintKey;
	// Shoot cooldown
	float _shootCooldown;
	// Shooth direction (if 0.0f should be the previous one)
	sf::Vector2f _shootDirection;

	sf::SoundBuffer _buffer_shoot;
	sf::Sound _sound_shoot;

public:
  void update(double dt) override;
	void render() override {};
  explicit PlayerControlsComponent(Entity* p);
  PlayerControlsComponent() = delete;
};
