#pragma once
#include <GL/glew.h>
namespace aw
{
    class Camera
    {
    private:
        float FOV, aspectRatio;

    public:
        Camera(float FOV, float aspectRatio);
        void setFOV(float FOV);
        void setAspectRatio(float aspectRatio);
    };
}