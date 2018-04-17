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
#include "components/cmp_interactable.h"
#include "enemies_states.h"
#include "key_states.h"
#include "door_states.h"
#include "main_collectible_states.h"
#include "fake_wall_states.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> create_player()
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
	player->addTag("player");

	auto s = player->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(0, 32 * 3, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = player->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width - 8, s->getSprite().getLocalBounds().height));
	p->getBody()->SetSleepingAllowed(false);
	p->getBody()->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	p->getBody()->SetBullet(true);

	player->addComponent<PlayerHealthComponent>();

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
		auto enemy_A = Engine::GetActiveScene()->makeEntity();
		enemy_A->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		enemy_A->addTag("enemy");
		enemy_A->addTag("enemy_A");

		auto s = enemy_A->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 32 * 5, 32, 32 - 4));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto sm = enemy_A->addComponent<StateMachineComponent>();
		sm->setName("ai");
		sm->addState("idle", make_shared<EnemyA_IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("chase", make_shared<EnemyA_ChaseState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("return", make_shared<EnemyA_ReturnState>(enemy_A->getPosition(), Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("prepare_attack", make_shared<EnemyA_PrepareAttackState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("attack", make_shared<EnemyA_AttackState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->changeState("idle");

		auto h = enemy_A->addComponent<EnemyHealthComponent>(3);

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
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 32 * 4, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto sm = enemy_B->addComponent<StateMachineComponent>();
		sm->setName("ai");
		sm->addState("idle", make_shared<EnemyB_IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("move", make_shared<EnemyB_MoveState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("shoot", make_shared<EnemyB_ShootState>());
		sm->changeState("idle");

		enemy_B->addComponent<EnemyHealthComponent>(3);

		auto p = enemy_B->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
		p->getBody()->SetBullet(true);

		auto h = enemy_B->addComponent<HurtComponent>("player");
		h->setActive(true);

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
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(32 * 2, 32 * 5, 32, 32)); // TEMPORARY
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto sm = enemy_C->addComponent<StateMachineComponent>();
		sm->setName("ai");
		sm->addState("idle", make_shared<EnemyC_IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("flee", make_shared<EnemyC_FleeState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("shoot", make_shared<EnemyC_ShootState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->changeState("idle");

		auto h = enemy_C->addComponent<EnemyHealthComponent>(2);

		auto p = enemy_C->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
		p->getBody()->SetBullet(true);

		enemies.push_back(enemy_C);
	}

	return enemies;
}

void create_walls()
{
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2);
		auto e = Engine::GetActiveScene()->makeEntity();
		e->addTag("wall");
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
	}

	auto fake_walls = ls::findTiles(ls::FAKE_WALL);
	for (auto w : fake_walls)
	{
		auto e = Engine::GetActiveScene()->makeEntity();
		e->setPosition(ls::getTilePosition(w) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		e->addTag("fake wall");

		auto s = e->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto sm = e->addComponent<StateMachineComponent>();
		sm->addState("hidden", make_shared<FakeWall_HiddenState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("revealed", make_shared<FakeWall_RevealedState>());
		sm->changeState("hidden");
	}
}

shared_ptr<Entity> create_button(string text)
{
	auto button = Engine::GetActiveScene()->makeEntity();
	button->addTag("button");

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(500.0f, 34.0f));
	s->getShape().setOrigin(s->getShape().getLocalBounds().width / 2, s->getShape().getLocalBounds().height / 2);

	auto t = button->addComponent<TextComponent>(text);
	// For some reason text is not centered
	t->getText()->setOrigin(t->getText()->getOrigin().x, t->getText()->getOrigin().y + 14.0f);
	t->getText()->setColor(Color(198, 152, 127));

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
	Vector2f pos = player->getPosition() + (33.0f * direction);
	e->setPosition(pos);

	auto s = e->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32 * 4, 32 * 3, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = e->addComponent<PhysicsComponent>(true, Vector2f(1.0f, 1.0f));
	p->getBody()->SetBullet(true);

	auto h = e->addComponent<HurtComponent>("enemy");
	h->setActive(true);

	direction.y *= -1; // physics and graphics have y inverted
	auto b = e->addComponent<BulletComponent>(&(*player), direction, 600.0f);

	return e;
}

shared_ptr<Entity> create_enemy_B_bullet(Entity* owner, Vector2f direction)
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("bullet");

	// Start position is near the player
	Vector2f pos = owner->getPosition() + (33.0f * direction);
	e->setPosition(pos);

	auto s = e->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32 * 2, 32 * 4, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = e->addComponent<PhysicsComponent>(true, Vector2f(1.0f, 1.0f));
	p->getBody()->SetBullet(true);

	auto h = e->addComponent<HurtComponent>("player");
	h->setActive(true);

	direction.y *= -1; // physics and graphics have y inverted
	auto b = e->addComponent<BulletComponent>(owner, direction, 600.0f);

	return e;
}

shared_ptr<Entity> create_enemy_C_bullet(Entity* owner, Vector2f direction)
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("bullet");

	// Start position is near the player
	Vector2f pos = owner->getPosition() + (33.0f * direction);
	e->setPosition(pos);

	auto s = e->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32 * 4, 32 * 5, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = e->addComponent<PhysicsComponent>(true, Vector2f(1.0f, 1.0f));
	p->getBody()->SetBullet(true);

	auto h = e->addComponent<HurtComponent>("player");
	h->setActive(true);

	direction.y *= -1; // physics and graphics have y inverted
	auto b = e->addComponent<BulletComponent>(owner, direction, 500.0f);

	return e;
}

shared_ptr<Entity> create_key()
{
	auto key = Engine::GetActiveScene()->makeEntity();
	key->setPosition(ls::getTilePosition(ls::findTiles(ls::KEY)[0]) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
	key->addTag("key");

	auto s = key->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(0, 32 * 2 + 4, 32, 32 - 4));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto sm = key->addComponent<StateMachineComponent>();
	sm->addState("not taken", make_shared<Key_NotTakenState>());
	sm->addState("taken", make_shared<Key_TakenState>(Engine::GetActiveScene()->ents.find("player")[0]));
	sm->addState("used", make_shared<Key_UsedState>());
	sm->changeState("not taken");

	key->addComponent<InteractableComponent>();

	return key;
}

shared_ptr<Entity> create_door()
{
	auto door = Engine::GetActiveScene()->makeEntity();
	door->setPosition(ls::getTilePosition(ls::findTiles(ls::DOOR)[0]) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
	door->addTag("door");

	auto s = door->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	s->getSprite().setTextureRect(sf::IntRect(32 * 7, 0, 32 * 3, 32 * 3));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = door->addComponent<PhysicsComponent>(false, Vector2f(s->getSprite().getGlobalBounds().width, s->getSprite().getGlobalBounds().height));

	auto sm = door->addComponent<StateMachineComponent>();
	sm->addState("close", make_shared<Door_CloseState>(Engine::GetActiveScene()->ents.find("player")[0]));
	sm->addState("open", make_shared<Door_OpenState>());
	sm->changeState("close");

	return door;
}

shared_ptr<Entity> create_baby_llama(int index)
{
	// 1 -> right
	// 2 -> top
	// 3 -> left

	Vector2ul llama_tile;
	switch (index)
	{
	case 1:
		llama_tile = ls::findTiles(ls::MAIN_COLLECTIBLE_RIGHT)[0];
		break;
	case 2:
		llama_tile = ls::findTiles(ls::MAIN_COLLECTIBLE_TOP)[0];
		break;
	case 3:
		llama_tile = ls::findTiles(ls::MAIN_COLLECTIBLE_LEFT)[0];
		break;
	default:
		break;
	}

	auto llama = Engine::GetActiveScene()->makeEntity();
	llama->setPosition(ls::getTilePosition(llama_tile) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
	llama->addTag("main collectible");

	auto s = llama->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("tex.png");
	s->setTexture(tex);
	switch (index)
	{
	case 1:
		s->getSprite().setTextureRect(sf::IntRect(32 * 7, 32 * 5, 32, 32));
		break;
	case 2:
		s->getSprite().setTextureRect(sf::IntRect(32 * 8, 32 * 5, 32, 32));
		break;
	case 3:
		s->getSprite().setTextureRect(sf::IntRect(32 * 9, 32 * 5, 32, 32));
		break;
	default:
		break;
	}
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = llama->addComponent<PhysicsComponent>(true, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));
	p->getBody()->SetFixedRotation(true);

	auto sm = llama->addComponent<StateMachineComponent>();
	sm->addState("lost", make_shared<MainCollectible_LostState>(Engine::GetActiveScene()->ents.find("player")[0]));
	sm->addState("happy", make_shared<MainCollectible_HappyState>());
	sm->addState("idle", make_shared<MainCollectible_IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
	sm->changeState("lost");

	return llama;
}

vector<shared_ptr<Entity>> create_potions()
{
	vector<shared_ptr<Entity>> potions;

	auto potion_tiles = ls::findTiles(ls::POTION);
	for (auto t : potion_tiles)
	{
		auto potion = Engine::GetActiveScene()->makeEntity();
		potion->setPosition(ls::getTilePosition(t) + Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2));
		potion->addTag("potion");

		auto s = potion->addComponent<SpriteComponent>();
		auto tex = Resources::get<Texture>("tex.png");
		s->setTexture(tex);
		s->getSprite().setTextureRect(sf::IntRect(32 * 6, 32 * 2, 32, 32));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		auto p = potion->addComponent<PhysicsComponent>(false, Vector2f(s->getSprite().getLocalBounds().width, s->getSprite().getLocalBounds().height));

		potion->addComponent<InteractableComponent>();

		potions.push_back(potion);
	}

	return potions;
}