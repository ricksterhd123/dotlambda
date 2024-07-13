# dotlambda

WIP 3D game stack:
- raylib for audio/math/graphics/rendering, ... as much as possible
- bullet3d for physics
- R7RS scheme for scripting

## Pre-requisites
- GNU/Linux x86 (built on WSL)
- cmake
- chibi-scheme (run `bash scripts/install-chibi.sh`)
- Raylib (https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) and its dependencies

## Setup
- `bash scripts/build.sh`

## Run
- `./dotlambda`

## TODO

## Client Side
- [x] scripting API
### Math
- [ ] Vector3 (WIP 13/07/24 -)
- [ ] Matrix
- [ ] Quarternions
### World
- [ ] Camera
- [ ] Element
    - [ ] Fx
    - [ ] Shader
    - [ ] Physics
### GUI
- [ ] GUI elements
### Audio
- [ ] 2D audio
- [ ] 3D audio element
### Events
- [ ] timers
- [ ] event system
### Input
- [ ] keyboard/mouse
- [ ] joystick
### Input events
- [ ] input event triggers

## Server-side
### Authentication / Authorization
- Use 
### RPC events
- trigger client-side event handlers
