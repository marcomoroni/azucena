#pragma once

#include <ecm.h>

class HurtComponent : public Component
{
private:
	int _damage = 1;

public:
	void update(double) override;
	void render() override {};
	explicit HurtComponent(Entity* p);
	HurtComponent() = delete;
	void setDamage(int);
};