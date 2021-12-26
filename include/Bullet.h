#pragma once
#include <GameObject.h>
namespace aw
{
    class Bullet : public GameObject
    {
    private:
        float speed = 20.0f;

    public:
        Bullet(std::shared_ptr<Mesh> mesh, GameObject *parent, glm::vec3 projectVec);
        void start() override;
        void update() override;
    };
}