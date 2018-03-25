#include "cmp_enemy_health.h"
#include "system_resources.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

RenderTexture backTex;
bool _flagHeathChanged = false;

EnemyHealthComponent::EnemyHealthComponent(Entity* p, int maxHealth)
	: Component(p), _maxHealth(maxHealth), _health(maxHealth)
{
	_tex = Resources::load<Texture>("enemy_health.png");
	
	// Create healt bar sprite 
	backTex.create(_spriteSize * _maxHealth, _spriteSize);
	backTex.clear(Color::Yellow);
	for (int i = 0; i < _maxHealth; i++)
	{
		auto s = Sprite();
		s.setTexture(*_tex);
		if (i == 0)
		{
			s.setTextureRect(IntRect(0, 0, _spriteSize, _spriteSize));
		}
		else if (i < _maxHealth - 1)
		{
			s.setTextureRect(IntRect(_spriteSize, 0, _spriteSize, _spriteSize));
		}
		else
		{
			s.setTextureRect(IntRect(_spriteSize * 2, 0, _spriteSize, _spriteSize));
		}
		s.setPosition({ (float)_spriteSize * i, 0 });
		backTex.draw(s);
	}
	backTex.display();
	_backSprite = make_shared<Sprite>(Sprite(backTex.getTexture()));
	_backSprite->setOrigin(_backSprite->getLocalBounds().width / 2, _backSprite->getLocalBounds().height / 2);

	// Create heart sprites
	for (int i = 0; i < _maxHealth; i++)
	{
		auto s = Sprite();
		s.setTexture(*_tex);
		s.setTextureRect(IntRect(0, _spriteSize, _spriteSize, _spriteSize));
		s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);
		_heartSprites.push_back(make_shared<Sprite>(s));
	}

}

void EnemyHealthComponent::update(double dt)
{
	_backSprite->setPosition(_parent->getPosition() + Vector2f(0, 40.0f));
	for (int i = 0; i < _heartSprites.size(); i++)
	{
		auto s = _heartSprites[i];
		s->setPosition(_backSprite->getPosition());
		s->setPosition({ (s->getPosition().x - _backSprite->getLocalBounds().width / 2 + (float)_spriteSize / 2) + (float)_spriteSize * i, s->getPosition().y });
	}

	if (_flagHeathChanged)
	{
		for (int i = 0; i < _heartSprites.size(); i++)
		{
			auto s = _heartSprites[i];
			if (i + 1 > _health) s->setTextureRect(IntRect(_spriteSize, _spriteSize, _spriteSize, _spriteSize));
			else s->setTextureRect(IntRect(0, _spriteSize, _spriteSize, _spriteSize));
		}
		_flagHeathChanged = false;
	}
}

void EnemyHealthComponent::render()
{
	//Renderer::queue(_testSprite.get());
	Renderer::queue(_backSprite.get());
	for (auto s : _heartSprites) Renderer::queue(s.get());
}

void EnemyHealthComponent::decreaseHealth(int h)
{
	int newHealth = _health - h;
	if (newHealth >= 0) _health = newHealth;
	_flagHeathChanged = true;

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

int EnemyHealthComponent::GetHealth() { return _health; }

int EnemyHealthComponent::GetMaxHealth() { return _maxHealth; }