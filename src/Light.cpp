#include <Light.h>
using namespace aw;
using namespace glm;

Light::Light(
	unsigned id,
	glm::vec4 ambient,
	glm::vec4 diffuse,
	glm::vec4 specular,
	glm::vec3 position) : id(id),
						  enabled(true),
						  type(POINT),
						  ambient(ambient),
						  diffuse(diffuse),
						  specular(specular),
						  angle(360.0f)
{
	transform = Transform(position, vec3(0, 0, 0), vec3(1, 1, 1));
	glEnable(GL_LIGHT0 + id);
}
Light::Light(
	unsigned id,
	glm::vec4 ambient,
	glm::vec4 diffuse,
	glm::vec4 specular,
	glm::vec3 position,
	glm::vec3 direction,
	float angle) : id(id),
				   enabled(true),
				   type(SPOT),
				   ambient(ambient),
				   diffuse(diffuse),
				   specular(specular),
				   angle(angle)
{
	if (angle > 360.0f || angle < 0.0f)
		throw "Light angle must be between 0 and 360 degrees.";

	transform = Transform(position, direction, vec3(1, 1, 1));
	glEnable(GL_LIGHT0 + id);
}
Light::Light(unsigned id, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, LightType type, glm::vec3 direction)
{
	if (type == POINT)
		Light(id, ambient, diffuse, specular, direction);
	else if (type == DIRECTIONAL)
	{
		this->id = id;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->type = DIRECTIONAL;
		transform = Transform(vec3(0, 0, 0), direction, vec3(1, 1, 1));
		glEnable(GL_LIGHT0 + id);
	}
	else
	{
		throw "Incorrect use of Light constructor with LightType::SPOT.";
	}
}
void Light::update()
{
	if (type == DIRECTIONAL)
	{
		GLfloat light_direction[] = {transform.getRotationAxis().x, transform.getRotationAxis().y, transform.getRotationAxis().z, 0.0f};
		glLightfv(GL_LIGHT0 + id, GL_POSITION, light_direction);
	}
	else
	{
		GLfloat light_position[] = {transform.getPosition().x, transform.getPosition().y, transform.getPosition().z, 1.0f};
		glLightfv(GL_LIGHT0 + id, GL_POSITION, light_position);
	}
	GLfloat light_ambient[] = {ambient.r, ambient.g, ambient.b, ambient.a};
	GLfloat light_diffuse[] = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
	GLfloat light_specular[] = {specular.r, specular.g, specular.b, specular.a};
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, light_specular);
}