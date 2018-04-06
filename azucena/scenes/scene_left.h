#pragma once

#include "engine.h"

class LeftScene : public Scene {
public:
  void Load() override;
  void UnLoad() override;
  void Update(const double& dt) override;
  void Render() override;

private:
  float _escButtonTimePressed = 0.0f;
  sf::Vector2f _view_center;
};
