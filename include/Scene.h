#pragma once
#include <vector>
#include <fstream>
#include <rapidjson/document.h>
#include <GameObject.h>
#include <Camera.h>
#include <StaticGO.h>
#include <Player.h>
#include <Ant.h>
#include <RagedAnt.h>
#include <Light.h>
#include <Skybox.h>
namespace aw
{
    /** \brief GameObject types, used to create the underlying object
     * type when parsing GameObject elements from a scene file.
     */
    enum CLASSES
    {
        STATICGO = 1,
        PLAYER = 2,
        ANT = 3,
        SKYBOX = 4,
        RAGED_ANT = 5
    };
    /** \brief Game level data descriptor, contains GameObject instances, Light instances
     * a camera instance and a skybox instance.
    */
    class Scene
    {
    public:
        /** \brief Parses scene ::gameObjects,::lights,::camera and ::skybox from file.
         *
         * \param path The path of the scene file on the drive.
         */
        Scene(const char *path);
        /** \brief Frees ::gameObjects instances from the heap.*/
        ~Scene();
        std::vector<GameObject *> gameObjects;
        std::vector<Light> lights;
        Camera camera;
        Skybox skybox = Skybox(nullptr, nullptr);
        /** \brief Destroys GameObject with \a index from ::gameObjects array.
         *
         * \param index The index of the target GameObject to destroy.
         */
        void destroyGameObject(int index);
    };
}