
# Building instructions

## Windows (Out-of-date, works on version 1.0)

### Required tools

- [Python 3 (3.10.0 or later)](https://www.python.org/downloads/)
- [Ninja build](https://ninja-build.org/)
- Visual Studio with C++ development tools (VS Community 2019 is recommended)

### Instructions

### Prerequisites

- Make sure `python3, pip3, ninja` are available in your PATH.
- Install meson using pip3 by running `pip3 install meson` under a command prompt with administrative privileges.
- Make the `antware` repository your working directory.

### Building for development (`debug`)

- Run `meson setup build --buildtype=debug` to setup the build directory.
- Run `meson compile -C build` to compile the project and it's dependencies.
- Copy `subprojects/sfml_winXX/SFML-X.X.X/bin/openal32.dll` to the root of the repository.
- Run `build/ant-warrior.exe` with the working directory set to the repository root.

### Building for production (`release`)

- Run `meson setup release --buildtype=release` to setup the build directory.
- Run `meson compile -C release` to compile the project and it's dependencies.
- Copy `subprojects/sfml_winXX/SFML-X.X.X/bin/openal32.dll` to the root of the repository.
- Run `release/ant-warrior.exe` with the working directory set to the repository root.

## Linux Debian

### Installing Tools:

```
sudo apt install build-essential ninja-build pkgconf
pip3 install meson
```

### Installing Dependnecies:

```
sudo apt install libsfml-dev libglew-dev libglm-dev libassimp-dev librapidjson-dev
```

### Building with Meson :
```
meson <your build dir> --buildtype=release
ninja -C<your build dir>
```

# Setting up settings
After these steps you should have your executable named ``ant-warrior`` within your build directory.

Make a copy of ``default_settings.json`` and modify it for your settings.

Rename your settings file to ``settings.json``.

Place your settings file in the executable directory.
