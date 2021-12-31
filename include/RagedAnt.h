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
        std::vector<std::shared_ptr<Mesh>> walkcycleAnim;
        std::shared_ptr<Mesh> baseMesh;

    public:
        RagedAnt(std::vector<std::shared_ptr<Mesh>> walkcycleAnim, std::shared_ptr<Mesh> mesh, Material material, GameObject *parent, GameObject *target);
        void die() override;
        void start() override;
        void update() override;
    };
}