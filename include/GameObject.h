#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <Mesh.h>
#include <Transform.h>
#include <Rigidbody.h>
#include <AABB.h>
namespace aw
{
    class GameObject
    {
    protected:
        std::shared_ptr<Mesh> meshPtr;
        GameObject *parent;
        std::vector<GameObject *> children;
        glm::mat4 transformationMat;
        int classType;

        void constructAABB();
        void recalculateAABB();

    public:
        Transform transform;
        Rigidbody rigidbody;
        Material material;
        AABB aabb;
        std::vector<GameObject *> getChildren();
        bool isStatic;

        GameObject(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent = nullptr, bool isStatic = false, int type = 1);
        GameObject(Mesh mesh, Material material, GameObject *parent = nullptr, bool isStatic = false, int type = 1);
        GameObject *getParent();
        void setParent(GameObject *parent);
        std::shared_ptr<Mesh> getMesh();
        void setMesh(std::shared_ptr<Mesh> mesh);
        glm::mat4 applyTransform();
        virtual void draw();
        void drawAABB(glm::vec3 color);
        virtual void fixedUpdate(float deltaTime);
        void addChild(GameObject *gameObject);
        int getClass();
        virtual void start() = 0;
        virtual void update() = 0;
    };
}