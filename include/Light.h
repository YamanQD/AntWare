#pragma once
#include <GL/glew.h>
#include <Transform.h>
#include <glm/glm.hpp>
namespace aw
{
	enum LightType
	{
		DIRECTIONAL,
		POINT,
		SPOT
	};

	class Light
	{
	private:
		unsigned id;
		bool enabled;
		LightType type;
		glm::vec4 ambient, diffuse, specular;
		float angle;

	public:
		Transform transform;
		Light(unsigned id, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 position);									// point light
		Light(unsigned id, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 position, glm::vec3 direction, float angle); // spot light
		Light(unsigned id, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, LightType type, glm::vec3 direction);					// directional light
		void setAmbient(glm::vec4 ambient);
		void setDiffuse(glm::vec4 diffuse);
		void setSpecular(glm::vec4 specular);
		void setAngle(float angle);
		void update();
		void toggle();
	};
}