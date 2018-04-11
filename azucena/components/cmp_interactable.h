#pragma once

#include <ecm.h>
#include <SFML/Audio.hpp>

class InteractableComponent : public Component
{
private:
	bool _active;
	float _playerInteractionDistance;
	Entity* _player;
	Entity* _interactionTimerSprite;
	float _interactionTimeNeeded;
	float _interactionTimer;
	bool _interacted;

	// Sounds
	sf::SoundBuffer _buffer_interactionTimer;
	sf::Sound _sound_interactionTimer;
	sf::SoundBuffer _buffer_interacted;
	sf::Sound _sound_interacted;

public:
	void update(double dt) override;
	void render() override {}
	explicit InteractableComponent(Entity* p, float playerInteractionDistance = 50.0f, float interactionTime = 1.4f);
	InteractableComponent() = delete;
	bool interacted();
	void setActive(bool);
};