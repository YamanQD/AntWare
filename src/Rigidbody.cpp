#include <Rigidbody.h>
using namespace aw;
using namespace glm;
void Rigidbody::lockLinear(AXIS axis)
{
    linearLock |= axis;
}
void Rigidbody::lockAngular(AXIS axis)
{
    angularLock |= axis;
}
void Rigidbody::unlockLinear(AXIS axis)
{
    linearLock ^= axis;
}
void Rigidbody::unlockAngular(AXIS axis)
{
    angularLock ^= axis;
}
bool Rigidbody::isLinearLocked(AXIS axis)
{
    return linearLock & axis;
}
bool Rigidbody::isAngularLocked(AXIS axis)
{
    return angularLock & axis;
}