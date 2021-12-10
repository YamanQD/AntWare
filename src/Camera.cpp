#include <Camera.h>
using namespace aw;
Camera::Camera(float FOV, float aspectRatio) : FOV(FOV), aspectRatio(aspectRatio)
{
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
}
void Camera::setFOV(float FOV)
{
    this->FOV = FOV;
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
}
void Camera::setAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    gluPerspective(FOV, aspectRatio, 0.1f, 100.0f);
}