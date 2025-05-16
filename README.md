# hyprmagnifier

A wlroots-compatible Wayland magnifier that does not suck

![hyprmagnifierShort](./example.gif)

# Usage

Just launch it.

## Options

See `hyprmagnifier --help`.

# Building

## Manual

Install dependencies:
 - cmake
 - pkg-config
 - pango
 - cairo
 - wayland
 - wayland-protocols
 - hyprutils
 - xkbcommon

Building is done via CMake:

```sh
cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=/usr -S . -B ./build
cmake --build ./build --config Release --target hyprmagnifier -j`nproc 2>/dev/null || getconf _NPROCESSORS_CONF`
```

Install with:

```sh
cmake --install ./build
```

# Caveats

"Freezes" your displays when picking the color.
