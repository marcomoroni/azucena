#pragma once

#include <ecm.h>

class InteractableComponent : public Component
{
private:
  float _playerInteractionDistance;
  Entity* _player;
  Entity* _pickUpTimerSprite;

public:
  void update(double dt) override;
  void render() override {}
  explicit InteractableComponent(Entity* p, float playerInteractionDistance = 50.0f);
  InteractableComponent() = delete;
};