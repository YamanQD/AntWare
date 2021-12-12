#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace aw
{
    class Transform
    {
    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

    public:
        Transform(glm::vec3 position,
                  glm::quat rotation = glm::quat(), // TODO make sure that is 0,0,0 eular angles rotation
                  glm::vec3 scale = {0, 0, 0});
        glm::vec3 getPosition();
        glm::quat getRotation();
        glm::vec3 getScale();
        void setPosition(glm::vec3 position);
        void setRotation(glm::quat rotation);
        void setScale(glm::vec3 scale);
    };
}