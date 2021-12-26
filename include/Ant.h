#pragma once
#include <GameObject.h>
namespace aw
{
    class Ant : public GameObject
    {
        public:
            Ant(std::shared_ptr<Mesh> mesh, GameObject *parent);
            void start() override;
            void update() override;
    };
}