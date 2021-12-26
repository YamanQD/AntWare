#include <StaticGO.h>
using namespace aw;
using namespace std;
StaticGO::StaticGO(shared_ptr<Mesh> mesh, GameObject *parent) : GameObject(mesh, parent, true, 1) {}
void StaticGO::start()
{
    isStatic = true;
}
void StaticGO::update()
{
}