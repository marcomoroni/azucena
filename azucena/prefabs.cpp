#include "prefabs.h"
#include "engine.h"
#include <LevelSystem.h>
#include <system_resources.h>

#include "components/cmp_player_controls.h"
#include "components/cmp_sprite.h"
#include "components/cmp_physics.h"
#include "components/cmp_state_machine.h"
#include "components/cmp_enemy_health.h"
#include "components/cmp_text.h"
#include "components/cmp_button.h"
#include "components/cmp_game_ui.h"
#include "components/cmp_player_health.h"
#include "components/cmp_hurt.h"
#include "components/cmp_bullet.h"
#include "enemies_states.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> create_player()
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
	player->addTag("player");

	auto s = player->addComponent<SpriteComponent>();
	auto tex = Resources::load<Texture>("invaders_sheet.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32, 0, 32, 32));
	// Centre origin
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	//player->addComponent<PlayerControlsComponent>(Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
	auto p = player->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
	p->getBody()->SetSleepingAllowed(false);
	p->getBody()->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	p->getBody()->SetBullet(true);

	player->addComponent<PlayerHealthComponent>(6);

	player->addComponent<PlayerControlsComponent>();

	return player;
}

vector<shared_ptr<Entity>> create_enemies()
{
	vector<shared_ptr<Entity>> enemies;

	// Enemy A
	auto enemy_A_tiles = ls::findTiles(ls::ENEMY_A);
	for (auto t : enemy_A_tiles)
	{
		auto enemy_A = Engine::GetActiveScene()-> makeEntity();
		enemy_A->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		enemy_A->addTag("enemy");
		enemy_A->addTag("enemy_A");

		auto s = enemy_A->addComponent<SpriteComponent>();
		auto tex = Resources::load<Texture>("invaders_sheet.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(64, 0, 32, 32));
		// Centre origin
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto sm = enemy_A->addComponent<StateMachineComponent>();
    sm->setName("ai");
		sm->addState("idle", make_shared<IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("chase", make_shared<ChaseState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("return", make_shared<ReturnState>(enemy_A->getPosition()));
		sm->addState("prepare_attack", make_shared<PrepareAttackState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("attack", make_shared<AttackState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->changeState("idle");

		auto h = enemy_A->addComponent<EnemyHealthComponent>(2);

		auto p = enemy_A->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
		p->getBody()->SetBullet(true);

		enemy_A->addComponent<HurtComponent>("player");

		enemies.push_back(enemy_A);
	}

	// Enemy B
	auto enemy_B_tiles = ls::findTiles(ls::ENEMY_B);
	for (auto t : enemy_B_tiles)
	{
		auto enemy_B = Engine::GetActiveScene()->makeEntity();
		enemy_B->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		enemy_B->addTag("enemy");
		enemy_B->addTag("enemy_B");

		auto s = enemy_B->addComponent<SpriteComponent>();
		auto tex = Resources::load<Texture>("invaders_sheet.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(96, 0, 32, 32));
		// Centre origin
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto h = enemy_B->addComponent<EnemyHealthComponent>(4);

		auto p = enemy_B->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
		p->getBody()->SetBullet(true);

		enemies.push_back(enemy_B);
	}

	// Enemy C
	auto enemy_C_tiles = ls::findTiles(ls::ENEMY_C);
	for (auto t : enemy_C_tiles)
	{
		auto enemy_C = Engine::GetActiveScene()->makeEntity();
		enemy_C->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		enemy_C->addTag("enemy");
		enemy_C->addTag("enemy_C");

		auto s = enemy_C->addComponent<SpriteComponent>();
		auto tex = Resources::load<Texture>("invaders_sheet.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(128, 0, 32, 32));
		// Centre origin
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto h = enemy_C->addComponent<EnemyHealthComponent>(2);

		auto p = enemy_C->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
		p->getBody()->SetBullet(true);

		enemies.push_back(enemy_C);
	}

	return enemies;
}

void add_physics_colliders_to_tiles()
{
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2); //offset to center
		auto e = Engine::GetActiveScene()->makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
	}
}

shared_ptr<Entity> create_button(string text)
{
	auto button = Engine::GetActiveScene()->makeEntity();
	button->addTag("button");

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(300.0f, 30.0f));
	s->getShape().setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	auto t = button->addComponent<TextComponent>(text);

	button->addComponent<ButtonComponent>(s, t);

	return button;
}

shared_ptr<Entity> create_game_ui()
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addComponent<GameUIComponent>(Engine::GetActiveScene()->ents.find("player")[0]);
	return e;
}

shared_ptr<Entity> create_player_bullet(Vector2f direction)
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("bullet");

	// Start position is near the player
	auto player = Engine::GetActiveScene()->ents.find("player")[0];
	// Note: has to be far enough from the player because it gets destroyed when it touches
	// something
	Vector2f pos = player->getPosition() + (50.0f * direction);
	e->setPosition(pos);

	auto s = e->addComponent<SpriteComponent>();
	auto tex = Resources::load<Texture>("invaders_sheet.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32, 32, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = e->addComponent<PhysicsComponent>(false, Vector2f(s->getSprite().getGlobalBounds().width, s->getSprite().getGlobalBounds().height));
	p->getBody()->SetBullet(true);

	auto h = e->addComponent<HurtComponent>("enemy"); // NOT WORKING ?
	h->setActive(true);

	auto b = e->addComponent<BulletComponent>(player, direction);

	return e;
}