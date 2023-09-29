#pragma once
#include <Ant.h>
namespace aw
{
/** \brief An ant that chases the Player.*/
class RagedAnt : public Ant {
private:
  /** \brief The target to chase, usually Player.*/
  GameObject *target;
  float speed = 8.0f;
  float detectionRaduis = 25.0f;
  /** \brief The meshes of the walking cycle animation.*/
  std::vector<std::shared_ptr<Mesh>> walkcycleAnim;
  std::shared_ptr<Mesh> baseMesh;
  float animTime = 0.0f;
  float walkcycleLength = 1.0f;

  /** \brief Progresses the walking cycle animation \a deltaTime seconds.
   *
   * \param deltaTime The amount of time, in seconds, to progress the animation.
   *
   * NOTE: This animation auto-loops.
   */
  void animate(float deltaTime);

public:
  /** \param walkcycleAnim The walking cycle animation Mesh instances.
   * \param mesh The RagedAnt's Mesh.
   * \param material The RagedAnt's Material.
   * \param parent The RagedAnt's parent.
   * \param target The target to look for and chase, usually the Player.
   */
  RagedAnt(std::vector<std::shared_ptr<Mesh>> walkcycleAnim,
           std::shared_ptr<Mesh> mesh, Material material, GameObject *parent,
           GameObject *target);
  /** \brief In addition to Ant::die, it sets the velocity to zero.*/
  void die() override;
  /** \brief In addition to Ant::start, it sets the texture of the
         * animation
   * meshes to the Ant's texture.*/
  void start() override;
  /** \brief In addition to Ant::update, setup the direction and velocity to
   * chase ::target, if ::target is visible, does nothing otherwise.
   */
  void update() override;
  /** \brief In addition to Ant::fixedUpdate, call ::animate( \a deltaTime ) if
   * the RagedAnt is moving, return to idle position if the RagedAnt is not
   * moving.
   */
  void fixedUpdate(float deltaTime) override;
};
}