#pragma once
#include <GameObject.h>
namespace aw {
/** \brief Basic GameObject, just a standing still Meshes, used for decorations
 * mostly.*/
class StaticGO : public GameObject {
public:
  /** \param mesh The GameObject's Mesh.
   * \param material The GameObject's Material.
   * \param parent The GameObject's parent.
   */
  StaticGO(std::shared_ptr<Mesh> mesh, Material material,
           GameObject *parent = nullptr);
  /** \brief Sets ::isStatic to true.*/
  void start() override;
  /** \brief Does nothing.*/
  void update() override;
};
} // namespace aw