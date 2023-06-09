# 2023 RISE Project

# Notes

This project was developed on Windows 10 using MSYS2 (MinGW64).
I tried as much as possible (without explicit effort) to make it work on Linux, but am unsure whether it'll work completely.

- SDL2 and its image/mixer libraries are available under the [zlib license](https://www.libsdl.org/license.php).
- The Steamworks SDK is available under the Steamworks [SDK Access Agreement](https://partner.steamgames.com/documentation/sdk_access_agreement).
- More credits and license information can be found in [CREDITS.md](./CREDITS.md)

# Dependencies

Anything below with `#` next to it means that whatever method of obtaining it should work, but that I used the system package manager (MSYS2's `pacman` in my case).

- [SDL2](https://www.libsdl.org/index.php) `#`
- [SDL2_image](https://github.com/libsdl-org/SDL_image) `#`
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer) `#`

## Steamworks

This is a bit of an unknown legal area for me. I mean, so is licensing in general, but zlib and CC-BY are way easier to understand.
Obtaining the [Steamworks SDK](https://partner.steamgames.com/downloads/steamworks_sdk_157.zip) requires an account and agreement to its license.
I am fairly confident that my use of it is acceptable (see [*Distributing Open Source Applications on Steam*](https://partner.steamgames.com/doc/sdk/uploading/distributing_opensource),
and this project specifically has been worked on mostly in an educational context.

The Steam Input API requires an IGA file be provided by the game developer.
Unfortunately, I'm not paying $100 to put my game on Steam.
In order to play the game on controller (which, as of now, is the *only* possible way),
you need to place the custom IGA file into your Steam root directory.
On Windows, usually this is `C:\Program Files (x86)\Steam\`.
On Linux and OSX, I have no clue.
In the Steam root, place the `game_actions_480.vdf` file into a folder called `controller_config`.
If it doesn't exist, create it.