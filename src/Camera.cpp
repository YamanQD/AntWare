#include <Camera.h>
using namespace aw;
Camera::Camera(float FOV, float aspectRatio) : FOV(FOV),aspectRatio(aspectRatio)
{
    //TODO @YamanQD
}
void Camera::setFOV(float FOV)
{
    this->FOV = FOV;
    //TODO @YamanQD
}
void Camera::setAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    //TODO @YamanQD
}