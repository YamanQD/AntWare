#pragma once
#include <GL/glew.h>
#include <Transform.h>
#include <Rigidbody.h>
namespace aw
{
    class Camera
    {
    private:
        float FOV;
        static float aspectRatio;

    public:
        Transform transform;
        Rigidbody rigidbody;

        Camera(float FOV);
        void setFOV(float FOV);
        void setAspectRatio(float aspectRatio);
        //Call to update camera matrices
        void update();
    };
}