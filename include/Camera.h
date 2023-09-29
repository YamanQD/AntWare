#pragma once
#include <GL/glew.h>
#include <Window.h>
#include <Transform.h>
#include <Rigidbody.h>
#include <GameObject.h>
namespace aw
{
  /** \brief %Camera abstraction, simulates a perspective view using perspective
   * matrix multiplication.*/
  class Camera
  {
  private:
    /** \brief The field-of-View value, in radians.*/
    float FOV;
    /** \brief The aspect ratio of the camera frustum, matches the window's
     * for
     * best resutlts.*/
    static float aspectRatio;
    /** \brief The transformation matrix from world space to perspective
     * camera
     * space.*/
    glm::mat4 viewPerspective;
    GLint viewPerspectiveLocation, posLocation;

  public:
    Transform transform;
    Rigidbody rigidbody;

    /** \brief Calculates ::aspectRatio using Window size.
     *
     * \param FOV Overwrites ::FOV.
     */
    Camera(float FOV);
    /** \param FOV overwrites ::FOV.
     * \param doUpdate call ::update if true, do nothing otherwise.
     */
    void setFOV(float FOV, bool doUpdate = true);
    /** \brief Updates ::aspectRatio and calls ::update.
     *
     * \param aspectRatio Overwrites ::aspectRatio.
     */
    void setAspectRatio(float aspectRatio);
    /** \brief Updates VP and observerPos variables in Shaders/main.vert and
     * Shaders/main.frag using viewPerspective and Transform::getPosition, in that
     * order.
     */
    void update();
    /** \brief Updates the physics properties and the transformation based
     * on
     * ::rigidbody data.*/
    void fixedUpdate(float deltaTime);
    /** \param location Overwrites ::viewPerspectiveLocation, the handle of the VP
     * matrix in Shaders/main.vert.
     */
    void setViewPerspectiveLocation(GLint location);
    /** \param location Overwrites ::posLocation, the handle of the observerPos
     * vector in Shaders/main.frag.
     */
    void setPosLoaction(GLint location);
  };
}