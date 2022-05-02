#include <Light.h>
using namespace aw;
using namespace std;
using namespace glm;

GLuint Light::UBO;
Light::Light(
	glm::vec4 ambient,
	glm::vec4 diffuse,
	glm::vec4 specular,
	glm::vec3 position,
	GameObject *parent) : lightStruct{.enabled = (true),
									  .type = (POINT),
									  .ambient = (ambient),
									  .diffuse = (diffuse),
									  .specular = (specular),
									  .angle = (180.0f)},
						  parent(parent)
{
	transform = Transform(position, vec3(0, 0, 0), vec3(1, 1, 1));
	update();
}
Light::Light(
	glm::vec4 ambient,
	glm::vec4 diffuse,
	glm::vec4 specular,
	glm::vec3 position,
	glm::vec3 direction,
	float angle,
	GameObject *parent) : lightStruct{.enabled = (true),
									  .type = (SPOT),
									  .ambient = (ambient),
									  .diffuse = (diffuse),
									  .specular = (specular),
									  .angle = (angle / 2.0f),
									  .direction = (direction)},
						  parent(parent)
{
	if (angle > 360.0f || angle < 0.0f)
		throw "Light angle must be between 0 and 360 degrees.";

	transform = Transform(position, direction, vec3(1, 1, 1));
	update();
}
Light::Light(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, LightType type, glm::vec3 direction, GameObject *parent) : parent(parent)
{
	if (type == POINT)
		*this = Light(ambient, diffuse, specular, direction, parent);
	else if (type == DIRECTIONAL)
	{
		this->lightStruct.ambient = ambient;
		this->lightStruct.diffuse = diffuse;
		this->lightStruct.specular = specular;
		this->lightStruct.type = DIRECTIONAL;
		this->lightStruct.direction = direction;
		transform = Transform(vec3(0, 0, 0), direction, vec3(1, 1, 1));
		update();
	}
	else
	{
		throw "Incorrect use of Light constructor with LightType::SPOT.";
	}
}
void Light::update()
{
}
void Light::toggle()
{
	lightStruct.enabled = !lightStruct.enabled;
	update();
}
Light::~Light()
{
}
void Light::constructUniformBuffer(const vector<Light> &lights)
{
	if (lights.size() > 20)
	{
		printf("requested more lights (%d) than the specified limit, ignoring past 20 lights",
			   lights.size());
	}
	vector<char> stagingBuffer(sizeof(LightStruct) * lights.size());
	for (unsigned i = 0; i < lights.size(); ++i)
	{
		memcpy(stagingBuffer.data() + i * sizeof(LightStruct),
			   &lights[i].lightStruct, sizeof(lightStruct));
	}
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightStruct) * lights.size(),
				 stagingBuffer.data(), GL_DYNAMIC_DRAW);
	assert(glGetError() == 0);
}