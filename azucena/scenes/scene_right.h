#pragma once

#include "engine.h"
#include <SFML/Audio.hpp>

class RightScene : public Scene {
public:
  void Load() override;
  void UnLoad() override;
  void Update(const double& dt) override;
  void Render() override;

private:
  std::shared_ptr<Entity> _player;
  std::shared_ptr<Entity> _door;
  float _escButtonTimePressed = 0.0f;
  sf::Vector2f _view_center;

	// Music
	std::shared_ptr<sf::Music> _music_overworld;
};
