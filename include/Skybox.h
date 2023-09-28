#pragma once
#include <GameObject.h>
#include <Camera.h>
namespace aw
{
/** \brief A cube texture that's drawn in the background.*/
class Skybox : public GameObject {
private:
  Camera *camera;

public:
  /** \param camera The main camera used in the Scene.
   * \param texture The path to the cube texture.
   */
  Skybox(Camera *camera, const char *texture);
  /** \brief Does nothing.*/
  void start() override;
  /** \brief Does nothing*/
  void update() override;
  /** \brief Draws the cube texture wrapped around the camera without writing
   * depth values. keeping the cube at infinity.
   */
  void draw() override;
};
}