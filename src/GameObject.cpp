#include <GameObject.h>
using namespace aw;
using namespace glm;
using namespace std;

GameObject::GameObject(shared_ptr<Mesh> mesh, GameObject *parent) : meshPtr(mesh),
																	parent(parent) {}
GameObject::GameObject(Mesh mesh, GameObject *parent) : meshPtr(make_shared<Mesh>(mesh)),
														parent(parent) {}

mat4 GameObject::applyTransform()
{
	mat4 parentMat(1.0f);
	if (parent != nullptr)
		parentMat = parent->applyTransform();

	vec3 translation = transform.getPosition();
	vec3 scale = transform.getScale();

	mat4 transMat = translate(mat4(1.0f), translation);
	mat4 rotationMat = mat4(transform.getRotation());
	mat4 scaleMat = glm::scale(mat4(1.0f), scale);
	
	mat4 transform = transMat * rotationMat * scaleMat;

	glMultMatrixf(&transform[0][0]);
	return parentMat * transform;
}

void GameObject::draw()
{
	glPushMatrix();
	transformationMat = applyTransform();
	meshPtr->draw();
	glPopMatrix();
}
