#pragma once
#include <GameObject.h>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
namespace aw
{
  /** \brief Shot bullets projectiles.*/
  class Bullet : public GameObject
  {
  private:
    sf::Clock timer;
    /** \brief The amount of time (in seconds) to keep the bullet present before
     * destroying it.*/
    float lifeSpan = 5.0f;
    float speed = 40.0f;

  public:
    /** \param mesh The Bullet's Mesh.
     * \param material The Bullet's Material.
     * \param parent The Bullet's parent.
     * \param projectVec The direction of ::rigidbody velocity vector.
     */
    Bullet(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent,
           glm::vec3 projectVec);
    /** \brief Restarts ::timer.*/
    void start() override;
    /** \brief Does nothing.*/
    void update() override;
    /** \return true if the ::timer has elapsed more than ::lifeSpan.
     * \return false otherwise.
     */
    bool timeOut();
  };
} // namespace aw