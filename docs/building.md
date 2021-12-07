
# Building instructions

## Windows

> TODO: @rami write those

## Linux

### Installing Dependnecies:

#### On Debian-based distros:
```
sudo apt install libsfml-dev
sudo apt install rapidjson-dev
```

### Using Meson :
```
meson <your build dir>
cd <your build dir>
ninja
```
After these steps you should have your executable named ``ant-warrior`` within your build directory.

Make a copy of ``settings_example.json`` and modify it for your settings.

Rename your settings file to ``settings.json``.

Place your settings file in your cwd.
