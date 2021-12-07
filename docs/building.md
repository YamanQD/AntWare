
# Building instructions

## Dependencies :

- [SFML](https://www.sfml-dev.org)
- [RapidJSON](https://rapidjson.org/)

## Windows

> TODO: @rami write those

## Linux

Using Meson :
```
meson <your build dir>
cd <your build dir>
ninja
```
After these steps you should have your executable named ``ant-warrior`` within your build directory.

Make a copy of ``settings_example.json`` and modify it for your settings.

Place your settings file in your cwd.
