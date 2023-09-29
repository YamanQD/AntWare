#pragma once
#define MAX_LIGHTS 20
#include <GL/glew.h>
#include <Transform.h>
#include <glm/glm.hpp>
#include <GameObject.h>
namespace aw
{
  enum LightType
  {
    /** \brief Far away light, simulated as parrallel rays, such as sun light.*/
    DIRECTIONAL,
    /** \brief Omnidirectional light, like a lightpulp.*/
    POINT,
    /** \brief Directed cone-shaped spot light, like a flashlight.*/
    SPOT
  };

  /** \brief A simulated light, casts no shadow.
   *
   * NOTE: This class can hold any type of LightType, depending on what was passed
   * into the constructor.
   */
  class Light
  {
  private:
    /** \brief RAM struct of the %LightStruct in Shaders/main.frag.
     *
     * Uses padding variables to have the variables in the correct memory location
     * in the the shader and the RAM struct, the %LightStruct in the shader uses
     * std140 GLSL 3.3 layout.
     */
    struct LightStruct
    {
      int enabled;
      LightType type;
      float padding0, padding1;
      glm::vec4 ambient, diffuse, specular;
      glm::vec3 direction;
      float angle;
      glm::vec3 position;
      float padding2;
    } lightStruct;

    /** \brief Used to have complex Transform hierarchies.*/
    GameObject *parent = nullptr;
    /** \brief Used to determine the index of the light in the shader's
     * Lights array.
     */
    int index;

    static GLuint UBO;

  public:
    Transform transform;
    /** \brief Constructs a light of any \a type using the provided parameters.
     *
     * Some parameters are not needed for some types, the LightType::DIRECTIONAL
     * type needs only a \a direction vector (the other parameters can be
     * anything, prefebably zeros), the LightType::POINT type needs a \a position
     * only, and the LightType::SPOT needs a \a position , \a direction and an  \a
     * angle.
     *
     * \param ambient The ambience color vector (unsigned normalized RGBA) of the
     * light.
     * \param diffuse The diffuse color vector (unsigned normalized RGBA)
     * of the light.
     * \param specular The specular color vector (unsigned
     * normalized RGBA) of the light.
     * \param type LightType of the light.
     * \param position The position of the light, unused in LightType::DIRECTIONAL.
     * \param direction The direction of the light, unused in LightType::POINT.
     * \param angle The angle of the cone of the light, only used in
     * LightType::SPOT.
     * \param parent The parent of the light.
     */
    Light(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
          LightType type, glm::vec3 position, glm::vec3 direction, float angle,
          GameObject *parent = nullptr);
    /** \brief Does nothing.*/
    ~Light();
    /** \brief [DEPRACTED] NOT IMPLEMENTED, DO NOT CALL.*/
    void setAmbient(glm::vec4 ambient);
    /** \brief [DEPRACTED] NOT IMPLEMENTED, DO NOT CALL.*/
    void setDiffuse(glm::vec4 diffuse);
    /** \brief [DEPRACTED] NOT IMPLEMENTED, DO NOT CALL.*/
    void setSpecular(glm::vec4 specular);
    /** \brief [DEPRACTED] NOT IMPLEMENTED, DO NOT CALL.*/
    void setAngle(float angle);
    /** \brief Updates the light data in the Lights array in Shaders/main.frag.*/
    void update();
    /** \brief Toggles light on and off, calls ::update.*/
    void toggle();

    /** \brief Creates a uniform buffer with \a lights ::lightStructs values
     * during Scene creation.
     *
     * Binds the created uniform buffer to the Lights array in Shaders/main.frag.
     */
    static void constructUniformBuffer(std::vector<Light> &lights);
  };
}