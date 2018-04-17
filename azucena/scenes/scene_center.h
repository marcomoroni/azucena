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
	std::shared_ptr<Entity> _baby1;
	std::shared_ptr<Entity> _baby2;
	std::shared_ptr<Entity> _baby3;
	float _escButtonTimePressed = 0.0f;
	sf::Vector2f _view_center;

	// Into cutscene time
	std::shared_ptr<Entity> _zzz;
	std::shared_ptr<Entity> _ohmy;
	float _intoTime = 0.0f;

	// Outro cutscene time
	float _outroTime = 0.0f;
};
