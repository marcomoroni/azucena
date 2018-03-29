# Notes

We should use this to keep track of everything we have to write in the report and to help eachother know what we've done.

## General

### Editor

Remeber to change the editor indentation to 2 spaces (Sam wrote verything like that).

### Debug only code

Remember to put Debug only code inside

``` cpp
#if DEBUG
// God mode
#endif
```

### Continuous integration

[![Build status](https://ci.appveyor.com/api/projects/status/8sqlliuqw0d2a50g?svg=true)](https://ci.appveyor.com/project/marcomoroni/azucena)

Builds only `master` branch.

## Git

Do not commit to `master` branch unless a feature is complete or you want to tweak or change small details.

After you clone this repo remember to run

```
git submodule update --init --recursive
```

## `prefabs`

Use the functions here when loading a scene to create entities. Without this, you would have, for example, to copy paste the code to create the player into every scene.

## Map generation

`LevelSystem` has been changed so the tiles have textures instead of plain colours.

However, rendering a sprite for each tile makes the game slower, so the sprite of each tile gets drawn into a `Rendertexture` when the map is loaded. Then, only this `RenderTexture` (its sprite) gets rendered.

## Components

Components can have a `_name`. This makes easier to handle multiple components attached to an entity. For example, an enemy entity can have two `SatateMachineComponents`, one for the AI, and one for sprite selection.

### ~`PlayerPhysicsComponent`~ `PlayerControlsComponent`

I changed this to simulate top-down view movement.

I'm not using impulses because I couldn't get the movement I wanted. Instead, I'm setting the velocity of the physics component at every frame.

The player can sprint by pressing <kbd>Space</kbd>. You have to release the button and press it again to sprint again. You need to wait a little bit until you can sprint again.

Right now, player can shoot bullet entities by pressing <kbd>RShift</kbd>. These entities are created in real-time, but if we have time we can try to avoid this.

### `StateMachineComponent`

Not much to say.

### `EnemyHealthComponent`

Add this component to each enemy. It renders a health bar near the enemy.

### `PlayerHealthComponent`

Similar to `cmp_enemy_health`, but it also handles potions. After getting hit, player has immunity for a little while.

### `HurtComponent`

Add this component if the entity hurts something. Add a tag as a parameter when initialising this component: this tag correspont to which entities will be hurt. By default, this component does not hurt, you need to use `setActive(true)` to activate it.

For now it can only handle one tag.

### `ButtonComponent`

This component handles the different states of button (highlight, select).

It changes `TextComponent` and `ShapeComponent` of the parent.

### `GameUIComponent`

Only used for in-game UI, not main menu (for now).

Changing the renderer system to allow rendering things on different views is too complicated, so we can attach this component to an empty entity. In the `update` function this component will change its `_parent` position to the center of the current view. In this way it looks like is not moving.

### `StateMachineComponent`

Since there are no ways to reset values (for example a timer) in a `State` I had to add a `enterState()` virtual function. This function gets called every we change state.

### `BulletComponent`

Attach this to bullets. the entity will follow a straight line until it hits something (but the owner). When this happens (or a few seconds are passed, to avoid having infinite bullets) this component will delete its parent.

## AI

For enemy _A_, see notes.

## Smooth camera

Every scene has to set the view at least once when opened.

You can set a new `View` each frame. Remeber not to change scene before. For example:

``` cpp
void Level1Scene::Update(const double& dt)
{
	// Do not include code that can change a scene here

	// Set view
	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	view.setCenter(player->getPosition());
	Engine::GetWindow().setView(view);
	
	// Can include code that changes scene here
}
```

## Remappable controls

There is a `Controls` class that allows to store a lookup table for keyboard keys.

We set all controls for the first time in `Engine::Start()` by calling `Controls::initialise()`.

To set or change a keyboard key use

``` cpp
Controls::SetKeyboardKey("Up", Keyboard::W)
```

To get a keyboard key use

``` cpp
Controls::GetKeyboardKey("Up")
```

For example, to check if a key is pressed write

``` cpp
if (Keyboard::isKeyPressed(Controls::GetKeyboardKey("Up")))
{
	// Going up
}
```

## Menu

Press <kbd>Esc</kbd> for a while to return to menu.

## Resize window

Changes in `Engine::Start()`.
