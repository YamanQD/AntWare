#pragma once
#include <GL/glew.h>
#include <Window.h>
#include <Transform.h>
#include <Rigidbody.h>
#include <GameObject.h>
namespace aw
{
    class Camera
    {
    private:
        float FOV;
        static float aspectRatio;
        glm::mat4 viewPerspective;
        GLint viewPerspectiveLocation,posLocation;

    public:
        Transform transform;
        Rigidbody rigidbody;

        Camera(float FOV);
        void setFOV(float FOV, bool doUpdate = true);
        void setAspectRatio(float aspectRatio);
        // Call to update camera matrices
        void update();
        void fixedUpdate(float deltaTime);
        void setViewPerspectiveLocation(GLint location);
        void setPosLoaction(GLint location);
    };
}