#pragma once
#include <memory>
#include <Mesh.h>
#include <Transform.h>
namespace aw
{
    class GameObject
    {
    private:
        std::shared_ptr<Mesh> meshPtr;
        GameObject *parent;

    public:
        Transform transform;

        GameObject(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr);
        GameObject(Mesh mesh, GameObject *parent = nullptr);
        GameObject *getParent();
        void setParent(GameObject *parent);
        std::shared_ptr<Mesh> getMesh();
        void setMesh(std::shared_ptr<Mesh> mesh);
        void draw();
        virtual void update() = 0;
    };
}