#include <Material.h>
using namespace aw;
using namespace glm;

GLint Material::diffuseLoc;
GLint Material::ambientLoc;
GLint Material::specularLoc;
GLint Material::shininessLoc;
GLint Material::alphaLoc;

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
void Material::setAlpha(float alpha)
{
	this->alpha = alpha;
	ambient.a = alpha;
	diffuse.a = alpha;
	specular.a = alpha;
}
float Material::getAlpha()
{
	return alpha;
}
void Material::apply()
{
	glUniform4fv(ambientLoc, 1, &ambient.x);
	glUniform4fv(diffuseLoc, 1, &diffuse.x);
	glUniform4fv(specularLoc, 1, &specular.x);
	glUniform1f(shininessLoc, shininess);
	glUniform1f(alphaLoc, alpha);
	assert(glGetError() == 0);
}
void Material::setUniformsLocation(GLuint program)
{
	glUseProgram(program);
	ambientLoc = glGetUniformLocation(program, "material.ambient");
	diffuseLoc = glGetUniformLocation(program, "material.diffuse");
	specularLoc = glGetUniformLocation(program, "material.specular");
	shininessLoc = glGetUniformLocation(program, "material.shininess");
	alphaLoc = glGetUniformLocation(program, "material.alpha");
	assert(glGetError() == 0);
}