# Notes

## General

Remeber to change the editor indentation to 2 spaces (Sam wrote verything like that).

## Git

Do not commit in master branch unless a feature is complete or you want to tweak or change small details.

## Components

### `cmp_player_physics`

I changed this to simulate top-down view movement.

I'm not using impulses because I couldn't get the movement I wanted. Instead, I'm setting the velocity at every frame.

The player can sprint by pressing <kbd>Space</kbd>. You have to release the button and press it again to sprint again. You need to wait a little bit until you can sprint again.

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
