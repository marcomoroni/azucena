#pragma once

#include "engine.h"

class MenuScene : public Scene {
public:
	MenuScene() = default;
	~MenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;

private:
	std::shared_ptr<Entity> _btn_Start;
	std::shared_ptr<Entity> _btn_Continue;
	std::shared_ptr<Entity> _btn_Load;
	std::shared_ptr<Entity> _btn_Options;
	std::shared_ptr<Entity> _btn_Quit;
	// All buttons
	std::vector<std::shared_ptr<Entity>> _btns;
};
