#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace aw
{
    class Transform
    {
    private:
        glm::vec3 position;
        glm::qua<double> rotation;
        glm::vec3 scaling;

    public:
        Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::qua<double> rotation = glm::qua<double>(1.0f, 0.0f, 0.0f, 0.0f),
                  glm::vec3 scale = {1.0f, 1.0f, 1.0f});
        Transform(glm::vec3 position,
                  glm::vec3 rotation,
                  glm::vec3 scale = {1.0f, 1.0f, 1.0f});
        glm::vec3 getPosition();
        glm::quat getRotation();
        glm::vec3 getScale();
        glm::vec3 getRotationAxis();
        double getRotationAngle();
        void setPosition(glm::vec3 position);
        void setRotation(glm::qua<double> rotation);
        void setRotation(glm::vec3 rotation);
        void setRotation(glm::vec3 axis, float angle);
        void setScale(glm::vec3 scale);
        void translate(glm::vec3 translation);
        void rotate(glm::qua<double> rotation);
        void rotate(glm::vec3 rotation);
        void rotate(glm::vec3 axis, float angle);
        void rotateGlobal(glm::qua<double> rotation);
        void rotateGlobal(glm::vec3 rotation);
        void rotateGlobal(glm::vec3 axis, float angle);
        void scale(glm::vec3 scale);
    };
}