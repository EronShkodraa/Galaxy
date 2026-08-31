# Galaxy

A 3D spiral galaxy simulation built from scratch in C++ and OpenGL. Features 1 million stars with 30 different colors, nebula clouds, and a rotating elliptical galaxy with spiral arms. Fly through it in first-person.

## Features

- 1 million procedurally generated stars
- 30 different star colors with random shade variations
- Nebula clouds with soft glow
- Rotating spiral galaxy with 5 arms
- Elliptical galaxy shape with gradual edge fade
- First-person camera to fly through
- Distance fog for depth
- Retro beep sounds when moving

## Controls

| Key | Action |
|---|---|
| W / A / S / D | Move |
| Mouse | Look around |
| Space | Move up |
| Left Shift | Move down |
| Esc | Exit |

## Project Structure


## How It Works

Stars are generated along 5 spiral arms using a logarithmic spiral pattern. Each star gets a random color from 30 options with random brightness. Nebulae are scattered along the same arms for a gas cloud effect. The galaxy rotates with stars closer to the center moving faster than outer stars.

## Requirements

- Windows
- MSYS2 with MinGW64
- OpenGL 3.3 or higher
- GLFW, GLM, GLAD

## How to Compile

```bash
/mingw64/bin/g++ -std=c++17 -I./include -I./src -I/mingw64/include src/main.cpp src/glad.c -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32 -mwindows -o galaxy.exe