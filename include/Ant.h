#pragma once
#include <GameObject.h>
namespace aw
{
    class Ant : public GameObject
    {
        unsigned hp = 4;

    public:
        Ant(std::shared_ptr<Mesh> mesh, GameObject *parent);
        void start() override;
        void update() override;
        void damage(unsigned amount);
        unsigned getHp();
    };
}