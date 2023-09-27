#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace aw
{
    /** \brief Describes a 3D object transformation (position, rotation and scale)
     * in a 3D space.
     *
     * Provides methods to manipulate the transformation of the objects.
     * The created transformation is applied by scaling, rotating and translating,
     * in this order.
     */
    class Transform
    {
    private:
        glm::vec3 position;
        glm::qua<double> rotation;
        glm::vec3 scaling;

    public:
        /** \brief Creates a transfomation object from the provided parameters.
         *
         * \param position The position of the object.
         * \param rotation The rotation of the object as a quaternion.
         * \param scale The scale of the object in XYZ axis directions.
         *
         * The created transformation is constructed by scaling, rotating and translating
         * in this order.
         */
        Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::qua<double> rotation = glm::qua<double>(1.0f, 0.0f, 0.0f, 0.0f),
                  glm::vec3 scale = {1.0f, 1.0f, 1.0f});
        /** \brief Creates a transfomation object from the provided parameters.
         *
         * \param position The position of the object.
         * \param rotation The rotation of the object as eular angles, in degrees.
         * \param scale The scale of the object in XYZ axis directions.
         *
         * The created transformation is constructed by scaling, rotating and translating
         * in this order.
         */
        Transform(glm::vec3 position,
                  glm::vec3 rotation,
                  glm::vec3 scale = {1.0f, 1.0f, 1.0f});
        /** \return ::position.*/
        glm::vec3 getPosition();
        /** \return ::rotation (Quaternion).*/
        glm::quat getRotation();
        /** \return ::scale.*/
        glm::vec3 getScale();
        /** \return Rotation axis derived from ::rotation.*/
        glm::vec3 getRotationAxis();
        /** \return Rotation angle around rotation axis, in degrees.*/
        double getRotationAngle();
        void setPosition(glm::vec3 position);
        void setRotation(glm::qua<double> rotation);
        void setRotation(glm::vec3 rotation);
        void setRotation(glm::vec3 axis, float angle);
        void setScale(glm::vec3 scale);
        void translate(glm::vec3 translation);
        void translateGlobal(glm::vec3 translation);
        void rotate(glm::qua<double> rotation);
        void rotate(glm::vec3 rotation);
        void rotate(glm::vec3 axis, float angle);
        void rotateGlobal(glm::qua<double> rotation);
        void rotateGlobal(glm::vec3 rotation);
        void rotateGlobal(glm::vec3 axis, float angle);
        void scale(glm::vec3 scale);
    };
}