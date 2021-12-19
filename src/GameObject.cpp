#include <GameObject.h>
using namespace aw;
using namespace glm;
using namespace std;

GameObject::GameObject(shared_ptr<Mesh> mesh, GameObject *parent) : meshPtr(mesh),
																	parent(parent) {}
GameObject::GameObject(Mesh mesh, GameObject *parent) : meshPtr(make_shared<Mesh>(mesh)),
														parent(parent) {}

void GameObject::applyTransform()
{
	if (parent != nullptr)
		parent->applyTransform();

	vec3 translation = transform.getPosition();
	vec3 rotation = transform.getRotationAxis();
	float angle = transform.getRotationAngle();
	vec3 scale = transform.getScale();

	glTranslatef(translation.x, translation.y, translation.z);
	glRotatef(angle, rotation.x, rotation.y, rotation.z);
	glScalef(scale.x, scale.y, scale.z);
}

void GameObject::draw()
{
	glPushMatrix();
	applyTransform();
	meshPtr->draw();
	glPopMatrix();
}
