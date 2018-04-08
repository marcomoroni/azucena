#pragma once

#include <ecm.h>

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

public:
  void update(double dt) override;
  void render() override {}
  explicit InteractableComponent(Entity* p, float playerInteractionDistance = 50.0f, float interactionTime = 1.0f);
  InteractableComponent() = delete;
  bool interacted();
  void setActive(bool);
};