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
     *
     * NOTE: The rotation axis mentioned in many places passes through the object's
     * geometrical center (model-space origin).
     *
     * NOTE: Using Y as up vector, X as right vector and Z as forward vector.
     *
     * NOTE: The "global space" is actually the parent's space if the GameObject (or any other
     * class that have a parent) has a parent present.
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
        /** \param position Overwrites ::position.*/
        void setPosition(glm::vec3 position);
        /** \param rotation Overwrites ::rotation.*/
        void setRotation(glm::qua<double> rotation);
        /** \param rotation Build a quaternion overwriting ::rotation
         *  from euler angles (pitch, yaw, roll), in degrees.*/
        void setRotation(glm::vec3 rotation);
        /** \param axis The axis of the new rotation
         * \param angle The angle of the new rotation around ::axis, in degrees.
         */
        void setRotation(glm::vec3 axis, float angle);
        /** \param scale Overwrites ::scale.*/
        void setScale(glm::vec3 scale);
        /** \brief Translates (moves) the object from ::position to ::position + \a translation (in local space)
         * ,Overwrites ::position to the new location.
         *
         * \param translation Specifies the vector (in local space) translating the object from its
         * current ::position.
         */
        void translate(glm::vec3 translation);
        /** \brief Translates (moves) the object from ::position to ::position + \a translation (in global space)
         * ,Overwrites ::position to the new location.
         *
         * \param translation Specifies the vector (in global space) translating the object from its
         * current ::position.
         */
        void translateGlobal(glm::vec3 translation);
        /** \brief Rotates the object with \a rotation (in local space)
         * , Overwrites ::rotation to the new rotation.
         *
         * \param rotation A quaternion representing the rotation (in local space)
         * to apply on the current one.
         */
        void rotate(glm::qua<double> rotation);
        /** \brief Rotates the object with \a rotation (in local space),
         * Overwrites ::rotation to the new rotation.
         *
         * \param rotation The rotation to value to rotate, from
         * euler angles (pitch, yaw, roll) (in local space), in degrees.
         */
        void rotate(glm::vec3 rotation);
        /** \brief Rotates the object with \a axis (in local space) and \a angle,
         * Overwrites ::rotation to the new rotation.
         *
         * \param axis The axis vector of which to rotate around (in local space).
         * \param angle The amount of rotation around \a axis , in degrees.
         */
        void rotate(glm::vec3 axis, float angle);
        /** \brief Rotates the object with \a rotation (in global space)
         * , Overwrites ::rotation to the new rotation.
         *
         * \param rotation A quaternion representing the rotation (in global space)
         * to apply on the current one.
         */
        void rotateGlobal(glm::qua<double> rotation);
        /** \brief Rotates the object with \a rotation (in global space),
         * Overwrites ::rotation to the new rotation.
         *
         * \param rotation The rotation to value to rotate, from
         * euler angles (pitch, yaw, roll) (in global space), in degrees.
         */
        void rotateGlobal(glm::vec3 rotation);
        /** \brief Rotates the object with \a axis (in global space) and \a angle,
         * Overwrites ::rotation to the new rotation.
         *
         * \param axis The axis vector of which to rotate around (in global space).
         * \param angle The amount of rotation around \a axis , in degrees.
         */
        void rotateGlobal(glm::vec3 axis, float angle);
        /** \brief Scales the object.
         *
         * \param scale The amount to scale, in global space.
         */
        void scale(glm::vec3 scale);
    };
}