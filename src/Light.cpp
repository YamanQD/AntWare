#include <Light.h>
#include <Renderer.h>
using namespace aw;
using namespace std;
using namespace glm;

GLuint Light::UBO;
Light::Light(vec4 ambient, vec4 diffuse, vec4 specular, LightType type, vec3 position, vec3 direction,
			 float angle, GameObject *parent) : parent(parent)
{
	lightStruct.ambient = ambient;
	lightStruct.angle = angle/2.0f;
	lightStruct.diffuse = diffuse;
	lightStruct.direction = direction;
	lightStruct.enabled = true;
	lightStruct.position = position;
	lightStruct.specular = specular;
	lightStruct.type = type;
	transform = Transform(position, direction);
}
void Light::update()
{
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(LightStruct) * index, sizeof(LightStruct), &lightStruct);
	assert(glGetError() == 0);
}
void Light::toggle()
{
	lightStruct.enabled = !lightStruct.enabled;
	update();
}
Light::~Light()
{
}
void Light::constructUniformBuffer(vector<Light> &lights)
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
		lights[i].index = i;
	}
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightStruct) * lights.size(),
				 stagingBuffer.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	int lightsIndex = glGetUniformBlockIndex(RENDERER.getMainShader(), "Lights");
	glUniformBlockBinding(RENDERER.getMainShader(), lightsIndex, 0);
	assert(glGetError() == 0);
}