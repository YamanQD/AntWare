#pragma once
#include <GameObject.h>
#include <Camera.h>
namespace aw
{
    class Skybox : public GameObject
    {
    private:
        Camera *camera;

    public:
        Skybox(Camera *camera, const char *texture);
        void start() override;
        void update() override;
        void draw() override;
    };
}