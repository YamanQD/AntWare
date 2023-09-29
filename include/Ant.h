#pragma once
#include <GameObject.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
namespace aw
{
  /** \brief Static non-moving ants.*/
  class Ant : public GameObject
  {
  protected:
    unsigned hp = 5;
    sf::Clock timeSinceDamage, timeSinceLastAlphaDecrease;
    Material originalMaterial;
    bool isHurting = false;
    bool isAlive = true;
    sf::SoundBuffer hurtSoundBuffer;
    sf::Sound hurtSound;
    /** \brief Switches Ant to dying state, flips it on its back
     *
     * Switches ::isHurting to false, ::isAlive to false and flips the Ant upside
     * down.
     */
    virtual void die();

  public:
    sf::Clock timeSinceDealtDamage;

    /** \param mesh The Ant's Mesh.
     * \param material The Ant's Material.
     * \param parent The Ant's parent.
     */
    Ant(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent);
    /** \brief Does nothing.*/
    void start() override;
    /** \brief Updates the Ant visuals depending on its state.*/
    void update() override;
    /** \brief Deals damage to Ant, if ::hp reaches zero or below, transit to
     * dying state.
     *
     * \param amount The value that is removed from ::hp.
     */
    void damage(unsigned amount);
    /** \return ::hp*/
    unsigned getHp();
    /** \return true if ::isAlive is false and ::material::getAlpha returns zero.
     * \return false otherwise.
     */
    bool timeToDestroy();
  };
}