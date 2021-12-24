#include <Material.h>
using namespace aw;
using namespace glm;

Material::Material(
	vec4 ambient,
	vec4 diffuse,
	vec4 specular,
	float shininess) : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
Material::Material() : ambient({0.1f, 0.1f, 0.1f, 1.0f}),
					   diffuse({0.6f, 0.6f, 0.6f, 1.0f}),
					   specular({0.3f, 0.3f, 0.3f, 1.0f}),
					   shininess(8.0f) {}
void Material::setAmbient(vec4 ambient)
{
	this->ambient = ambient;
}
void Material::setDiffuse(vec4 diffuse)
{
	this->diffuse = diffuse;
}
void Material::setSpecular(vec4 specular)
{
	this->specular = specular;
}
void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}
void Material::apply()
{
	GLfloat mat_ambient[] = {ambient.r, ambient.g, ambient.b, ambient.a};
	GLfloat mat_diffuse[] = {diffuse.r, diffuse.g, diffuse.b, diffuse.a};
	GLfloat mat_specular[] = {specular.r, specular.g, specular.b, specular.a};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}