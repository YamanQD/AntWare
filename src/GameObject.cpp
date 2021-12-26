#include <GameObject.h>
using namespace aw;
using namespace glm;
using namespace std;

GameObject::GameObject(shared_ptr<Mesh> mesh, GameObject *parent, bool isStatic, int type) : meshPtr(mesh),
																							 isStatic(isStatic),
																							 classType(type)
{
	setParent(parent);
	constructAABB();
}
GameObject::GameObject(Mesh mesh, GameObject *parent, bool isStatic, int type) : meshPtr(make_shared<Mesh>(mesh)),
																				 isStatic(isStatic),
																				 classType(type)
{
	setParent(parent);
	constructAABB();
}

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
	recalculateAABB();
	meshPtr->draw();
	glPopMatrix();
}
void GameObject::fixedUpdate(float deltaTime)
{
	if (isStatic)
		return;
	rigidbody.velocity += rigidbody.acceleration * deltaTime;
	rigidbody.angularVelocity += rigidbody.angularAcceleration * deltaTime;
	vec3 appliedVelocity = mat3(transform.getRotation()) * rigidbody.velocity;
	vec3 appliedAngularVelocity = mat3(transform.getRotation()) * rigidbody.angularVelocity;
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
	transform.translateGlobal(appliedVelocity * deltaTime);
	transform.rotateGlobal(appliedAngularVelocity * deltaTime);
}
void GameObject::constructAABB()
{
	auto vertices = meshPtr->getVertices();
	aabb.backward = vertices[0].z;
	aabb.forward = vertices[0].z;
	aabb.down = vertices[0].y;
	aabb.up = vertices[0].y;
	aabb.right = vertices[0].x;
	aabb.left = vertices[0].x;
	for (unsigned i = 0; i < vertices.size(); ++i)
	{
		aabb.backward = glm::min(aabb.backward, vertices[i].z);
		aabb.forward = glm::max(aabb.forward, vertices[i].z);
		aabb.down = glm::min(aabb.down, vertices[i].y);
		aabb.up = glm::max(aabb.up, vertices[i].y);
		aabb.left = glm::min(aabb.left, vertices[i].x);
		aabb.right = glm::max(aabb.right, vertices[i].x);
	}
	for (unsigned i = 0; i < 8; ++i)
		aabb.bounds[i] = {0, 0, 0};
	aabb.bounds[0] = {aabb.right, aabb.up, aabb.forward};
	aabb.bounds[1] = {aabb.right, aabb.up, aabb.backward};
	aabb.bounds[2] = {aabb.right, aabb.down, aabb.forward};
	aabb.bounds[3] = {aabb.right, aabb.down, aabb.backward};
	for (unsigned i = 4; i < 8; ++i)
	{
		aabb.bounds[i] = aabb.bounds[i - 4];
		aabb.bounds[i].x = aabb.left;
	}
}
void GameObject::recalculateAABB()
{
	vec3 transformedBound = transformationMat * vec4(aabb.bounds[0], 1);
	aabb.backward = transformedBound.z;
	aabb.forward = transformedBound.z;
	aabb.down = transformedBound.y;
	aabb.up = transformedBound.y;
	aabb.right = transformedBound.x;
	aabb.left = transformedBound.x;
	for (unsigned i = 0; i < 8; ++i)
	{
		transformedBound = transformationMat * vec4(aabb.bounds[i], 1);
		aabb.backward = glm::min(aabb.backward, transformedBound.z);
		aabb.forward = glm::max(aabb.forward, transformedBound.z);
		aabb.down = glm::min(aabb.down, transformedBound.y);
		aabb.up = glm::max(aabb.up, transformedBound.y);
		aabb.left = glm::min(aabb.left, transformedBound.x);
		aabb.right = glm::max(aabb.right, transformedBound.x);
	}
}
GameObject *GameObject::getParent()
{
	return parent;
}
void GameObject::setParent(GameObject *gameObject)
{
	parent = gameObject;
	if (parent)
		parent->addChild(this);
}
void GameObject::addChild(GameObject *child)
{
	children.push_back(child);
}
vector<GameObject *> GameObject::getChildren()
{
	return children;
}
void GameObject::setMesh(shared_ptr<Mesh> mesh)
{
	this->meshPtr = mesh;
}