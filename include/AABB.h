#pragma once
#include <glm/glm.hpp>
namespace aw
{
/** \brief Axis-Aligned-Bounding-Box, used for intersections detection.*/
class AABB {
private:
  float up, down, right, left, forward, backward;

public:
  /** \brief The vertices of the AABB.*/
  glm::vec3 bounds[8];
  /** \param other The AABB to check if it intersects with this one.
   * \return true if the two AABBs are intersecting, false otherwise.
   */
  bool isColliding(const AABB &other);
  /** \param point The point that gets checked if it's inside (or on the sides)
   * the AABB or not. \return true if \a point is inside (or on the sides) of
   * the AABB, false otherwise.
   */
  bool isColliding(glm::vec3 point);
  /** \return The center of the AABB.*/
  glm::vec3 getCenter();
  /** \param factor The amount of which to reduce (NOT scale) the AABB
   * size.*/
  void minmize(float factor);
  /** \param factor The amount of which to increate (NOT scale) the AABB
   * size.*/
  void maximize(float factor);
  friend class GameObject;
};
}