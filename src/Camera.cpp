#include <Camera.h>
using namespace aw;
using namespace glm;
float Camera::aspectRatio;
Camera::Camera(float FOV) : FOV(FOV)
{
    aspectRatio = (float)WINDOW.internal.getSize().x / (float)WINDOW.internal.getSize().y;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(FOV, aspectRatio, 0.1f, 120.0f);

    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
}
void Camera::setFOV(float FOV)
{
    this->FOV = FOV;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glLoadIdentity();
    gluPerspective(FOV, aspectRatio, 0.1f, 120.0f);
    glPushMatrix();
    update();
}
void Camera::setAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glLoadIdentity();
    gluPerspective(FOV, aspectRatio, 0.1f, 120.0f);
    glPushMatrix();
    update();
}
void Camera::update()
{
    vec3 camPos = transform.getPosition();
    vec3 camDir = vec3(0, 0, -1);
    vec3 camUp = vec3(0, 1, 0);
    mat3 rotationMat = mat3(transform.getRotation());
    camDir = rotationMat * camDir;
    camUp = rotationMat * camUp;
    vec3 lookedAt = camDir + camPos;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPushMatrix();
    gluLookAt(camPos.x, camPos.y, camPos.z,
              lookedAt.x, lookedAt.y, lookedAt.z,
              camUp.x, camUp.y, camUp.z);
    glMatrixMode(GL_MODELVIEW);
}
void Camera::fixedUpdate(float deltaTime)
{
    rigidbody.velocity += rigidbody.acceleration * deltaTime;
    rigidbody.angularVelocity += rigidbody.angularAcceleration * deltaTime;
    vec3 appliedVelocity = rigidbody.velocity;
    vec3 appliedAngularVelocity = rigidbody.angularVelocity;
    if (rigidbody.isLinearLocked(AXIS::x))
        appliedVelocity.x = 0;
    if (rigidbody.isLinearLocked(AXIS::y))
        appliedVelocity.y = 0;
    if (rigidbody.isLinearLocked(AXIS::z))
        appliedVelocity.z = 0;
    if (rigidbody.isAngularLocked(AXIS::x))
        appliedAngularVelocity.x = 0;
    if (rigidbody.isAngularLocked(AXIS::y))
        appliedAngularVelocity.y = 0;
    if (rigidbody.isAngularLocked(AXIS::z))
        appliedAngularVelocity.z = 0;
    transform.translate(appliedVelocity * deltaTime);
    transform.rotate(appliedAngularVelocity * deltaTime);
}