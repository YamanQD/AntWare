#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <Mesh.h>
#include <Transform.h>
#include <Rigidbody.h>
#include <AABB.h>
namespace aw
{
/** \brief The building blocks of the game, defines elements that act on their
 * own, and interact with other elements.
 */
class GameObject {
protected:
  /** \brief The shared Mesh that's used to draw the GameObject*/
  std::shared_ptr<Mesh> meshPtr;
  /** \brief Used to have complex Transform hierarchies.*/
  GameObject *parent;
  /** \brief The GameObject instances which their parent is this
   * instance.*/
  std::vector<GameObject *> children;
  /** \brief Model transformation matrix, transforms the GameObject from
   * model-space to world-space.
   */
  glm::mat4 transformationMat;
  /** CLASSES value corresponding to the derived type of the GameObject.*/
  int classType;
  static GLuint modelLocation;

  /** \brief Builds ::aabb from model-space mesh.*/
  void constructAABB();
  /** \brief Rebuilds ::aabb after applying ::transformationMat.*/
  void recalculateAABB();

public:
  Transform transform;
  Rigidbody rigidbody;
  Material material;
  AABB aabb;
  std::vector<GameObject *> getChildren();
  bool isStatic;

  /** \param mesh The mesh of the GameObject.
   * \param material The material coating the mesh.
   * \param parent The transform parent of the GameObject.
   * \param isStatic Decides whether the GameObject has physics applied or not.
   * \param type The class type of the GameObject, a value of CLASSES.
   */
  GameObject(std::shared_ptr<Mesh> mesh, Material material,
             GameObject *parent = nullptr, bool isStatic = false, int type = 1);
  /** \param mesh The mesh of the GameObject.
   * \param material The material coating the mesh.
   * \param parent The transform parent of the GameObject.
   * \param isStatic Decides whether the GameObject has physics applied or not.
   * \param type The class type of the GameObject, a value of CLASSES.
   */
  GameObject(Mesh mesh, Material material, GameObject *parent = nullptr,
             bool isStatic = false, int type = 1);
  /** \return ::parent.*/
  GameObject *getParent();
  /** \param parent Overwrites ::parent.*/
  void setParent(GameObject *parent);
  /** \return ::meshPtr.*/
  std::shared_ptr<Mesh> getMesh();
  /** \param mesh Overwrites ::meshPtr.*/
  void setMesh(std::shared_ptr<Mesh> mesh);
  /** \return Applied the transformations recursivly (parent to parent),
   * returns
   * the final transformation matrix.*/
  glm::mat4 applyTransform();
  /** \brief Draws the mesh after applying the transformations*/
  virtual void draw();
  /** \brief [DEPRECATED] Used to draw AABB for debugging, uses Legacy OpenGL so
   * it doesn't work.
   *
   * \param color The color of the AABB lines (unsigned normalized RGBA).
   */
  void drawAABB(glm::vec3 color);
  /** \brief Applies the physics using ::rigidbody data, changing the GameObject
   * Transform. \param deltaTime The time (in seconds) between the last time
   * physics were applied and the present (commonly known as the timestep).
   */
  virtual void fixedUpdate(float deltaTime);
  /** \brief Adds \a gameObject to ::children.
   * \param gameObject The GameObject to be added to ::children.
   */
  void addChild(GameObject *gameObject);
  /** \return ::classType.*/
  int getClass();
  /** \brief Abstract function, is called at Scene::start.*/
  virtual void start() = 0;
  /** \brief Abstract function, is called at Scene::update.*/
  virtual void update() = 0;

  /** \param location Overwrites ::modelLocation, the handle to the M matrix in
   * Shaders/main.vert*/
  static void setModelLocation(GLuint location);
};
}