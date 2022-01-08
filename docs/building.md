
# Building instructions

## Windows

### Required tools

- [Python 3 (3.10.0 or later)](https://www.python.org/downloads/)
- [Ninja build](https://ninja-build.org/)
- Visual Studio with C++ development tools (VS Community 2019 is recommended)

### Instructions

- Make sure `python/python3, pip/pip3, ninja` are available in your PATH.
- Install meson using pip/pip3 by running `pip install meson` under a command prompt with administrative privileges.
- Make the `ant-warrior` repository your working directory.
- Run `meson subprojects download` to fetch dependencies.
- Run `meson setup build` to setup the build directory.
- Run `meson build -C build` to compile the project and it's dependencies.
- Copy `default_settings.json` to `build/settings.json` and modify it accourding to your preferences.
- Run `ant-warrior.exe`.

//TODO @rami, update Windows instructions

## Linux Debian

### Installing Tools:

```
sudo apt install build-essential cmake ninja-build
sudo pip3 install meson
```

### Installing Dependnecies:

```
sudo apt install libsfml-dev libglm-dev rapidjson-dev
sudo apt install libglu1-mesa-dev
```

### Building with Meson :
```
meson <your build dir>
cd <your build dir>
ninja
```
After these steps you should have your executable named ``ant-warrior`` within your build directory.

Make a copy of ``default_settings.json`` and modify it for your settings.

Rename your settings file to ``settings.json``.

Place your settings file in your cwd.
