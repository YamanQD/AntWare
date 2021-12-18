#include <GameObject.h>
using namespace aw;
using namespace glm;

void GameObject::applyTransform()
{
	GameObject *parent = getParent();

	vec3 translation = transform.getPosition();
	vec3 rotation = transform.getRotationAxis();
	float angle = transform.getRotationAngle();
	vec3 scale = transform.getScale();

	glTranslatef(translation.x, translation.y, translation.z);
	glRotatef(angle, rotation.x, rotation.y, rotation.z);
	glScalef(scale.x, scale.y, scale.z);

	if (parent != nullptr)
		parent->applyTransform();
}

void GameObject::draw()
{
	glPushMatrix();
	applyTransform();
	getMesh()->draw();
	glPopMatrix();
}
