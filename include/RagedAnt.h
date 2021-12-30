#pragma once
#include <Ant.h>
namespace aw
{
    class RagedAnt : public Ant
    {
    private:
        GameObject *target;
        float speed = 8.0f;
        float detectionRaduis = 30.0f;

    public:
        RagedAnt(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent, GameObject *target);
        void die() override;
        void update() override;
    };
}