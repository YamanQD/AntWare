#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <Mesh.h>
#include <Transform.h>
#include <Rigidbody.h>
namespace aw
{
    class GameObject
    {
    private:
        std::shared_ptr<Mesh> meshPtr;
        GameObject *parent;
        glm::mat4 transformationMat;

    public:
        Transform transform;
        Rigidbody rigidbody;
        bool isStatic;

        GameObject(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr, bool isStatic = false);
        GameObject(Mesh mesh, GameObject *parent = nullptr, bool isStatic = false);
        GameObject *getParent();
        void setParent(GameObject *parent);
        std::shared_ptr<Mesh> getMesh();
        void setMesh(std::shared_ptr<Mesh> mesh);
        glm::mat4 applyTransform();
        void draw();
        void fixedUpdate(float deltaTime);
        virtual void update() = 0;
    };
}