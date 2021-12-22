#pragma once
#include <GameObject.h>
namespace aw
{
    class StaticGO : public GameObject
    {
    public:
        StaticGO(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr);
        void start() override;
        void update() override;
    };
}