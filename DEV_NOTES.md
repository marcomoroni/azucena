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

## Git

Do not commit in master branch unless a feature is complete or you want to tweak or change small details.

## Components

### `cmp_player_physics`

I changed this to simulate top-down view movement.

I'm not using impulses because I couldn't get the movement I wanted. Instead, I'm setting the velocity at every frame.

The player can sprint by pressing <kbd>Space</kbd>. You have to release the button and press it again to sprint again. You need to wait a little bit until you can sprint again.

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

## Resize window

Changes in `Engine::Start()`.