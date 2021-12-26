#pragma once
#include <vector>
#include <fstream>
#include <rapidjson/document.h>
#include <GameObject.h>
#include <Camera.h>
#include <StaticGO.h>
#include <Player.h>
#include <Ant.h>
#include <Light.h>
namespace aw
{
    enum CLASSES
    {
        STATICGO = 1,
        PLAYER = 2,
        ANT = 3
    };
    class Scene
    {
    public:
        Scene(const char *path);
        ~Scene();
        std::vector<GameObject *> gameObjects;
        std::vector<Light> lights;
        Camera camera;
        void destroyGameObject(int index);
    };
}