#pragma once
#include <GL/glew.h>
#include <Transform.h>
namespace aw
{
    class Camera
    {
    private:
        float FOV, aspectRatio;

    public:
        Transform transform;

        Camera(float FOV, float aspectRatio);
        void setFOV(float FOV);
        void setAspectRatio(float aspectRatio);
        //Call to update camera matrices
        void update();
    };
}