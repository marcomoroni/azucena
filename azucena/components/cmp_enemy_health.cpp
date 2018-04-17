#include "cmp_enemy_health.h"
#include "system_resources.h"
#include "system_renderer.h"
#include "engine.h"
#include "cmp_sprite.h"

using namespace std;
using namespace sf;

//RenderTexture backTex;
bool _flagHeathChanged = false;

EnemyHealthComponent::EnemyHealthComponent(Entity* p, int maxHealth)
	: Component(p), _maxHealth(maxHealth), _health(maxHealth), _showHealthBar(false)
{
	int heartSpriteSize = 8;
	for (int i = 0; i < _maxHealth; i++)
	{
		auto e = Engine::GetActiveScene()->makeEntity();
		auto s = e->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(32 * 5, 32 * 4, heartSpriteSize, heartSpriteSize));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);
		s->getSprite().setOrigin(s->getSprite().getOrigin().x - ((_maxHealth * heartSpriteSize / 2) - heartSpriteSize / 2) + (heartSpriteSize * i), s->getSprite().getOrigin().y);
		e->setVisible(false); // Hide until gets hit

		_healthSprites.push_back(&(*e));
	}
}

void EnemyHealthComponent::update(double dt)
{
	if (_immunity >= 0.0f) _immunity -= dt;

	for (auto h : _healthSprites)
		h->setPosition(Vector2f(_parent->getPosition().x, _parent->getPosition().y + 40.0f));

	// Delete if health == 0
	if (_health <= 0)
	{
		_parent->setForDelete();

		// Also delete health bar
		for (auto h : _healthSprites) h->setForDelete();
	}
}

void EnemyHealthComponent::render()
{

}

void EnemyHealthComponent::decreaseHealth(int h)
{
	// Show health bar
	if (!_showHealthBar)
	{
		_showHealthBar = true;
		for (auto& e : _healthSprites)
		{
			e->setVisible(true);
		}
	}

	if (_immunity < 0.0f)
	{
		int newHealth = _health - h;
		if (newHealth >= 0) _health = newHealth;
		_immunity = 0.2f;
		_flagHeathChanged = true;

		// Change health sprite
		_healthSprites[_maxHealth - newHealth - 1]->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(IntRect(32 * 5 + 8, 32 * 4, 8, 8));
	}

}

void EnemyHealthComponent::decreaseHealth()
{
	decreaseHealth(1);
}

void EnemyHealthComponent::increaseHealth(int h)
{
	int newHealth = _health + h;
	if (newHealth < _maxHealth) _health = newHealth;
	_flagHeathChanged = true;
}

void EnemyHealthComponent::increaseHealth()
{
	increaseHealth(1);
}

int EnemyHealthComponent::getHealth() { return _health; }

int EnemyHealthComponent::getMaxHealth() { return _maxHealth; }