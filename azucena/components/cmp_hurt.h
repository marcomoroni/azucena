#pragma once

#include <ecm.h>
#include <string>

class HurtComponent : public Component
{
private:
	bool _active;
	int _damage = 1;
	std::string _tagToHurt;

public:
	void update(double) override;
	void render() override {};
	explicit HurtComponent(Entity* p, std::string tagToHurt);
	HurtComponent() = delete;
	void setDamage(int);
	void setActive(bool);
};