#include "entities_creator.h"
#include "engine.h"
#include <LevelSystem.h>
#include <system_resources.h>

#include "components/cmp_player_physics.h"
#include "components/cmp_sprite.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> create_player(Scene* scene)
{
	auto player = scene->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	auto s = player->addComponent<SpriteComponent>();
	auto tex = Resources::load<Texture>("invaders_sheet.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32, 0, 32, 32));
	// Centre origin
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	player->addComponent<PlayerPhysicsComponent>(Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));

	return player;
}

vector<shared_ptr<Entity>> create_enemies(Scene* scene)
{
	vector<shared_ptr<Entity>> enemies;

	// Enemy A
	auto enemy_A_tiles = ls::findTiles(ls::ENEMY_A);
	for (auto t : enemy_A_tiles)
	{
		auto enemy_A = scene-> makeEntity();
		enemy_A->setPosition(ls::getTilePosition(t));
		enemy_A->addTag("enemy");
		enemy_A->addTag("enemy_A");

		auto s = enemy_A->addComponent<SpriteComponent>();
		auto tex = Resources::load<Texture>("invaders_sheet.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(64, 0, 32, 32));
		// Centre origin
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		enemies.push_back(enemy_A);
	}

	// Enemy B
	auto enemy_B_tiles = ls::findTiles(ls::ENEMY_B);
	for (auto t : enemy_B_tiles)
	{
		auto enemy_B = scene->makeEntity();
		enemy_B->setPosition(ls::getTilePosition(t));
		enemy_B->addTag("enemy");
		enemy_B->addTag("enemy_B");

		auto s = enemy_B->addComponent<SpriteComponent>();
		auto tex = Resources::load<Texture>("invaders_sheet.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(96, 0, 32, 32));
		// Centre origin
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		enemies.push_back(enemy_B);
	}

	// Enemy C
	auto enemy_C_tiles = ls::findTiles(ls::ENEMY_C);
	for (auto t : enemy_C_tiles)
	{
		auto enemy_C = scene->makeEntity();
		enemy_C->setPosition(ls::getTilePosition(t));
		enemy_C->addTag("enemy");
		enemy_C->addTag("enemy_C");

		auto s = enemy_C->addComponent<SpriteComponent>();
		auto tex = Resources::load<Texture>("invaders_sheet.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(128, 0, 32, 32));
		// Centre origin
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		enemies.push_back(enemy_C);
	}

	return enemies;
}