#pragma once
#include <vector>
#include <fstream>
#include <rapidjson/document.h>
#include <GameObject.h>
#include <Camera.h>
#include <DummyGO.h>
#include <StaticGO.h>
namespace aw
{
    enum CLASSES
    {
        STATICGO = 1
    };
    class Scene
    {
    public:
        Scene(const char *path);
        ~Scene();
        std::vector<GameObject *> gameObjects;
        Camera camera;
        // TODO Light lights[8]
    };
}