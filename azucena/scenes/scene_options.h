#pragma once

#include "engine.h"
#include <map>

class OptionsScene : public Scene {
public:
	OptionsScene() = default;
	~OptionsScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

private:
  std::shared_ptr<Entity> _btn_ControlsUp;
  std::shared_ptr<Entity> _btn_ControlsDown;
  std::shared_ptr<Entity> _btn_ControlsLeft;
  std::shared_ptr<Entity> _btn_ControlsRight;
  std::shared_ptr<Entity> _btn_ControlsDash;
  std::shared_ptr<Entity> _btn_ControlsShoot;
  std::shared_ptr<Entity> _btn_ControlsInteract;
  std::shared_ptr<Entity> _btn_Back;
  // All buttons
  std::vector<std::shared_ptr<Entity>> _btns;
  // Map button to control
  std::map<std::shared_ptr<Entity>, std::string> _controlsBtns;
  // The control being changed
  std::shared_ptr<Entity> _changingControl = nullptr;
};
