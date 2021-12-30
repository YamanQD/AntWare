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
#include <Skybox.h>
namespace aw
{
    enum CLASSES
    {
        STATICGO = 1,
        PLAYER = 2,
        ANT = 3,
        SKYBOX = 4
    };
    class Scene
    {
    public:
        Scene(const char *path);
        ~Scene();
        std::vector<GameObject *> gameObjects;
        std::vector<Light> lights;
        Camera camera;
        Skybox skybox = Skybox(nullptr, nullptr);
        void destroyGameObject(int index);
    };
}