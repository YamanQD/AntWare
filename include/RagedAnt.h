#pragma once
#include <Ant.h>
namespace aw
{
    class RagedAnt : public Ant
    {
    private:
        GameObject *target;
        float speed = 8.0f;
        float detectionRaduis = 25.0f;
        std::vector<std::shared_ptr<Mesh>> walkcycleAnim;
        std::shared_ptr<Mesh> baseMesh;
        float animTime = 0.0f;
        float walkcycleLength = 1.0f;

        void animate(float deltaTime);

    public:
        RagedAnt(std::vector<std::shared_ptr<Mesh>> walkcycleAnim, std::shared_ptr<Mesh> mesh, Material material, GameObject *parent, GameObject *target);
        void die() override;
        void start() override;
        void update() override;
        void fixedUpdate(float deltaTime) override;
    };
}