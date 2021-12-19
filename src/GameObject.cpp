#include <GameObject.h>
using namespace aw;
using namespace glm;
using namespace std;

GameObject::GameObject(shared_ptr<Mesh> mesh, GameObject *parent, bool isStatic) : meshPtr(mesh),
																				   parent(parent),
																				   isStatic(isStatic) {}
GameObject::GameObject(Mesh mesh, GameObject *parent, bool isStatic) : meshPtr(make_shared<Mesh>(mesh)),
																	   parent(parent),
																	   isStatic(isStatic) {}

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
void GameObject::fixedUpdate(float deltaTime)
{
	if (isStatic)
		return;
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
void GameObject::constructAABB(){
	// TODO
}
void GameObject::recalculateAABB(){
	// TODO
}