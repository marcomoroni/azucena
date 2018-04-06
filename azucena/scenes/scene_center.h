#pragma once

#include "engine.h"

class CenterScene : public Scene {
public:
  void Load() override;
  void UnLoad() override;
  void Update(const double& dt) override;
  void Render() override;

private:
  std::shared_ptr<Entity> _player;
  float _escButtonTimePressed = 0.0f;
  sf::Vector2f _view_center;
};
