#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include "../azucena/controls.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../azucena/data.h"

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

bool Engine::_fullscreen = false;

void Loading_update(float dt, const Scene* const scn) {
	//  cout << "Eng: Loading Screen\n";
	if (scn->isLoaded()) {
		cout << "Eng: Exiting Loading Screen\n";
		loading = false;
	}
	else {
		loadingspinner += 180.0f * dt;
		loadingTime += dt;
	}
}
void Loading_render() {
	// cout << "Eng: Loading Screen Render\n";

	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	static Sprite loadingSprite;
	static Texture tex(*Resources::get<sf::Texture>("tex.png"));
	loadingSprite.setTexture(tex);
	loadingSprite.setTextureRect(sf::IntRect(0, 32 * 3, 32, 32));
	loadingSprite.setOrigin(loadingSprite.getLocalBounds().width / 2, loadingSprite.getLocalBounds().height / 2);
	loadingSprite.setPosition(Vcast<float>(Engine::getWindowSize()).x - 64.0f, Vcast<float>(Engine::getWindowSize()).y - 64.0f);
	loadingSprite.setRotation(loadingspinner);
	Renderer::queue(&loadingSprite);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		Physics::update(dt);
		_activeScene->Update(dt);
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	RenderWindow window;
	window.create(VideoMode(width, height), gameName);
	//window.create(VideoMode(width, height), gameName, Style::Titlebar | Style::Close);
	_gameName = gameName;
	_window = &window;
	Renderer::initialise(window);
	Physics::initialise();
	Controls::initialise();
	Data::reset();
	ChangeScene(scn);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			// Resize window
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			// Fullscreen
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::F11)
				{
					_fullscreen = !_fullscreen;
					window.create(VideoMode(width, height), gameName, (_fullscreen ? Style::Fullscreen : Style::Resize | Style::Close));
					//window.create(VideoMode(width, height), gameName, (_fullscreen ? Style::Fullscreen : Style::Titlebar | Style::Close));
					_window = &window;
				}
			}
		}

		window.clear(Color(44, 40, 38));
		Update();
		Render(window);
		window.display();
	}
	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}
	window.close();
	Physics::shutdown();
	// Render::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	ents.list.push_back(e);
	return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	// Notes:
	// * There is a `thread::sleep_for(3)` insode `Scene1.load().
	// * If the game crashes change `_activeScene->LoadAsync()` to `_activeScene->Load()`.

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->LoadAsync();
		loading = true;
	}
}

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			_loaded_future.get();
			_loaded = true;
		}
		return _loaded;
	}
}
void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	ents.list.clear();
	setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing

Scene::~Scene() { UnLoad(); }

Scene* Engine::GetActiveScene()
{
	return _activeScene;
}